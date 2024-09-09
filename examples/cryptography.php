<?php

    class Cryptography
    {
        // Generate a new RSA key pair
        public static function generateKeyPair()
        {
            // Generate private key
            $config = [
                "private_key_type" => OPENSSL_KEYTYPE_RSA,
                "private_key_bits" => 2048,
            ];
            $res = openssl_pkey_new($config);

            // Extract the private key to a variable
            openssl_pkey_export($res, $privateKey);

            // Extract the public key from the private key
            $publicKeyDetails = openssl_pkey_get_details($res);
            $publicKey = $publicKeyDetails['key'];

            // Return both keys in Base64 encoding (without PEM headers)
            return [
                'privateKey' => base64_encode($privateKey),
                'publicKey' => base64_encode($publicKey),
            ];
        }

        // Sign the content using the private key
        public static function signContent($content, $privateKey)
        {
            // Decode the Base64 private key
            $privateKeyDecoded = openssl_pkey_get_private(base64_decode($privateKey));

            // Sign the content
            openssl_sign($content, $signature, $privateKeyDecoded, OPENSSL_ALGO_SHA256);

            // Return the signature in Base64 encoding
            return base64_encode($signature);
        }

        // Verify the signature of the content using the public key
        public static function verifyContent($content, $signature, $publicKey)
        {
            // Decode the Base64 public key
            $publicKeyDecoded = openssl_pkey_get_public(base64_decode($publicKey));

            // Decode the Base64 signature
            $signatureDecoded = base64_decode($signature);

            // Verify the signature
            $result = openssl_verify($content, $signatureDecoded, $publicKeyDecoded, OPENSSL_ALGO_SHA256);

            // Return true if the signature is valid, false otherwise
            return $result === 1;
        }

        // Sign the content with a temporary signature based on time blocks
        public static function temporarySignContent($content, $privateKey, $frames = 1)
        {
            // Calculate the current time block
            $timeBlock = intdiv(time(), 60);

            // Append the time block to the content
            $contentWithTime = $content . '|' . $timeBlock;

            // Sign the content with the time block
            return self::signContent($contentWithTime, $privateKey);
        }

        // Verify a temporary signature with time blocks
        public static function verifyTemporarySignature($content, $signature, $publicKey, $frames = 1)
        {
            // Calculate the current time block
            $timeBlock = intdiv(time(), 60);

            // Check for each time block within the frame range
            for ($i = 0; $i < $frames; $i++) {
                // Append the time block to the content
                $contentWithTime = $content . '|' . ($timeBlock - $i);

                // Verify the signature
                if (self::verifyContent($contentWithTime, $signature, $publicKey)) {
                    return true;
                }
            }

            // Return false if none of the frames matched
            return false;
        }

        // Encrypt the content using the public key
        public static function encryptContent($content, $publicKey)
        {
            // Decode the Base64 public key
            $publicKeyDecoded = openssl_pkey_get_public(base64_decode($publicKey));

            // Encrypt the content
            openssl_public_encrypt($content, $ciphertext, $publicKeyDecoded, OPENSSL_PKCS1_OAEP_PADDING);

            // Return the ciphertext in Base64 encoding
            return base64_encode($ciphertext);
        }

        // Decrypt the content using the private key
        public static function decryptContent($ciphertext, $privateKey)
        {
            // Decode the Base64 private key
            $privateKeyDecoded = openssl_pkey_get_private(base64_decode($privateKey));

            // Decode the Base64 ciphertext
            $ciphertextDecoded = base64_decode($ciphertext);

            // Decrypt the content
            openssl_private_decrypt($ciphertextDecoded, $plaintext, $privateKeyDecoded, OPENSSL_PKCS1_OAEP_PADDING);

            // Return the decrypted plaintext
            return $plaintext;
        }
    }
