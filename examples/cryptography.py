import base64
import time
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.Cipher import PKCS1_OAEP

class Cryptography:

    @staticmethod
    def generate_key_pair():
        # Generate RSA key pair
        key = RSA.generate(2048)
        private_key = key.export_key(format='DER')
        public_key = key.publickey().export_key(format='DER')

        # Return keys in Base64 encoding
        return {
            'privateKey': base64.b64encode(private_key).decode('utf-8'),
            'publicKey': base64.b64encode(public_key).decode('utf-8')
        }

    @staticmethod
    def sign_content(content, private_key_base64):
        # Decode the Base64 private key
        private_key = RSA.import_key(base64.b64decode(private_key_base64))

        # Hash the content using SHA256
        h = SHA256.new(content.encode('utf-8'))

        # Sign the hash
        signature = pkcs1_15.new(private_key).sign(h)

        # Return the signature in Base64 encoding
        return base64.b64encode(signature).decode('utf-8')

    @staticmethod
    def verify_content(content, signature_base64, public_key_base64):
        # Decode the Base64 public key and signature
        public_key = RSA.import_key(base64.b64decode(public_key_base64))
        signature = base64.b64decode(signature_base64)

        # Hash the content
        h = SHA256.new(content.encode('utf-8'))

        try:
            # Verify the signature
            pkcs1_15.new(public_key).verify(h, signature)
            return True
        except (ValueError, TypeError):
            return False

    @staticmethod
    def temporary_sign_content(content, private_key_base64, frames=1):
        # Calculate the current time block
        time_block = int(time.time() // 60)

        # Append the time block to the content
        content_with_time = f"{content}|{time_block}"

        # Sign the content with the time block
        return Cryptography.sign_content(content_with_time, private_key_base64)

    @staticmethod
    def verify_temporary_signature(content, signature_base64, public_key_base64, frames=1):
        # Calculate the current time block
        time_block = int(time.time() // 60)

        # Check for each time block within the frame range
        for i in range(frames):
            content_with_time = f"{content}|{time_block - i}"
            if Cryptography.verify_content(content_with_time, signature_base64, public_key_base64):
                return True

        return False

    @staticmethod
    def encrypt_content(content, public_key_base64):
        # Decode the Base64 public key
        public_key = RSA.import_key(base64.b64decode(public_key_base64))

        # Encrypt the content using RSA-OAEP
        cipher = PKCS1_OAEP.new(public_key)
        ciphertext = cipher.encrypt(content.encode('utf-8'))

        # Return the ciphertext in Base64 encoding
        return base64.b64encode(ciphertext).decode('utf-8')

    @staticmethod
    def decrypt_content(ciphertext_base64, private_key_base64):
        # Decode the Base64 private key and ciphertext
        private_key = RSA.import_key(base64.b64decode(private_key_base64))
        ciphertext = base64.b64decode(ciphertext_base64)

        # Decrypt the content using RSA-OAEP
        cipher = PKCS1_OAEP.new(private_key)
        plaintext = cipher.decrypt(ciphertext)

        # Return the decrypted content
        return plaintext.decode('utf-8')

