#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// Base64 encoding
char* base64_encode(const unsigned char* buffer, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char* b64text = (char*)malloc(bufferPtr->length + 1);
    memcpy(b64text, bufferPtr->data, bufferPtr->length);
    b64text[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    return b64text;
}

// Base64 decoding
unsigned char* base64_decode(const char* b64message, size_t* out_len) {
    BIO *bio, *b64;
    int decodeLen = strlen(b64message);
    unsigned char* buffer = (unsigned char*)malloc(decodeLen);

    bio = BIO_new_mem_buf(b64message, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    *out_len = BIO_read(bio, buffer, decodeLen);

    BIO_free_all(bio);
    return buffer;
}

// Generate RSA key pair
RSA* generate_key_pair() {
    int bits = 2048;
    unsigned long exp = RSA_F4;

    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();
    BN_set_word(bn, exp);

    if (!RSA_generate_key_ex(rsa, bits, bn, NULL)) {
        fprintf(stderr, "RSA key generation failed\n");
        return NULL;
    }

    BN_free(bn);
    return rsa;
}

// Sign content using private key
char* sign_content(const char* content, RSA* privateKey) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)content, strlen(content), hash);

    unsigned char* signature = (unsigned char*)malloc(RSA_size(privateKey));
    unsigned int sig_len;

    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, &sig_len, privateKey) == 0) {
        fprintf(stderr, "Error signing content: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    char* encodedSignature = base64_encode(signature, sig_len);
    free(signature);
    return encodedSignature;
}

// Verify the signature of content using public key
int verify_content(const char* content, const char* signature_base64, RSA* publicKey) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)content, strlen(content), hash);

    size_t sig_len;
    unsigned char* signature = base64_decode(signature_base64, &sig_len);

    int verify = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature, sig_len, publicKey);
    free(signature);
    return verify;
}

// Encrypt content using public key
char* encrypt_content(const char* content, RSA* publicKey) {
    int data_len = strlen(content);
    unsigned char* encrypted = (unsigned char*)malloc(RSA_size(publicKey));

    if (RSA_public_encrypt(data_len, (unsigned char*)content, encrypted, publicKey, RSA_PKCS1_OAEP_PADDING) == -1) {
        fprintf(stderr, "Error encrypting content: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    char* encodedCiphertext = base64_encode(encrypted, RSA_size(publicKey));
    free(encrypted);
    return encodedCiphertext;
}

// Decrypt content using private key
char* decrypt_content(const char* ciphertext_base64, RSA* privateKey) {
    size_t encrypted_len;
    unsigned char* encrypted = base64_decode(ciphertext_base64, &encrypted_len);
    unsigned char* decrypted = (unsigned char*)malloc(RSA_size(privateKey));

    if (RSA_private_decrypt(encrypted_len, encrypted, decrypted, privateKey, RSA_PKCS1_OAEP_PADDING) == -1) {
        fprintf(stderr, "Error decrypting content: %s\n", ERR_error_string(ERR_get_error(), NULL));
        return NULL;
    }

    free(encrypted);
    return strdup((char*)decrypted);
}

// Temporary sign content based on time blocks
char* temporary_sign_content(const char* content, RSA* privateKey, int frames) {
    time_t time_block = time(NULL) / 60;
    char content_with_time[512];
    snprintf(content_with_time, sizeof(content_with_time), "%s|%ld", content, time_block);

    return sign_content(content_with_time, privateKey);
}

// Verify temporary signature
int verify_temporary_signature(const char* content, const char* signature_base64, RSA* publicKey, int frames) {
    time_t time_block = time(NULL) / 60;
    char content_with_time[512];

    for (int i = 0; i < frames; ++i) {
        snprintf(content_with_time, sizeof(content_with_time), "%s|%ld", content, time_block - i);
        if (verify_content(content_with_time, signature_base64, publicKey)) {
            return 1; // Verified successfully
        }
    }

    return 0; // Failed verification
}
