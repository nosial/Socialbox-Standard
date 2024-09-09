import java.security.*;
import java.util.Base64;
import javax.crypto.Cipher;
import java.time.Instant;

public class Cryptography {

    // Generate a new RSA key pair
    public static KeyPair generateKeyPair() throws NoSuchAlgorithmException {
        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("RSA");
        keyGen.initialize(2048);
        return keyGen.generateKeyPair();
    }

    // Sign the content using the private key
    public static String signContent(String content, PrivateKey privateKey) throws Exception {
        Signature privateSignature = Signature.getInstance("SHA256withRSA");
        privateSignature.initSign(privateKey);
        privateSignature.update(content.getBytes("UTF-8"));
        byte[] signature = privateSignature.sign();
        return Base64.getEncoder().encodeToString(signature);
    }

    // Verify the signature of the content using the public key
    public static boolean verifyContent(String content, String signature, PublicKey publicKey) throws Exception {
        Signature publicSignature = Signature.getInstance("SHA256withRSA");
        publicSignature.initVerify(publicKey);
        publicSignature.update(content.getBytes("UTF-8"));
        byte[] signatureBytes = Base64.getDecoder().decode(signature);
        return publicSignature.verify(signatureBytes);
    }

    // Sign the content with a temporary signature based on time blocks
    public static String temporarySignContent(String content, PrivateKey privateKey, int frames) throws Exception {
        long timeBlock = Instant.now().getEpochSecond() / 60;
        String contentWithTime = content + "|" + timeBlock;
        return signContent(contentWithTime, privateKey);
    }

    // Verify a temporary signature with time blocks
    public static boolean verifyTemporarySignature(String content, String signature, PublicKey publicKey, int frames) throws Exception {
        long timeBlock = Instant.now().getEpochSecond() / 60;

        for (int i = 0; i < frames; i++) {
            String contentWithTime = content + "|" + (timeBlock - i);
            if (verifyContent(contentWithTime, signature, publicKey)) {
                return true;
            }
        }

        return false;
    }

    // Encrypt the content using the public key
    public static String encryptContent(String content, PublicKey publicKey) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA/ECB/OAEPWithSHA-256AndMGF1Padding");
        cipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] ciphertext = cipher.doFinal(content.getBytes("UTF-8"));
        return Base64.getEncoder().encodeToString(ciphertext);
    }

    // Decrypt the content using the private key
    public static String decryptContent(String ciphertext, PrivateKey privateKey) throws Exception {
        Cipher cipher = Cipher.getInstance("RSA/ECB/OAEPWithSHA-256AndMGF1Padding");
        cipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(ciphertext));
        return new String(decryptedBytes, "UTF-8");
    }
}
