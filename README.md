# About Socialbox

This project is the Socialbox standard documentation, this project is intended to describe the standard for which
Socialbox servers and clients would use to communicate over the internet.

## What's Socialbox?

Socialbox is a decentralized platform for hosting social media instances, enabling users to register/authenticate on
various instances and communicate with other users or communities across different instances without relying on a
centralized server. This model aims to replace traditional services like Email, Reddit, and Twitter, allowing users
to create communities for private, internal, or public purposes and engage in peer-to-peer communication, even if
they are on different servers.

![The illustration of how a Decentralized paradise should look like](images%2Fdecentralized.png "Decentralized Illustration")
![How peers can talk to each other even when on different domains](images%2Fpeer2peer.png "Peer to Peer illustration")

## Why use Socialbox?

Email has been around for a long time, but it only allows us to send messages to each other but it's still great,
because it allows Alice from example.com to email John at foobar.com even if both users are on different
servers with the possibility of different features, but the underlying protocol still works to allow two users from
different servers to communicate with each other.

But take Twitter or Reddit for example, users are constrained to create their accounts or boards on that one and only
platform, if Reddit or anyone on that platform doesn't like that board, they could very well take it down and make it
inaccessible to many users. Even worse if Reddit goes down entirely! Socialbox aims to fix this to allow users to
explore the internet as it once was without being tied to a centralized service, so for example <john@foobar.com> may be
able to post on <cats@lol.com> and interact with other users that doesn't necessarily come from lol.com or foobar.com.
<john@foobar.com> may also subscribe to these channels and or boards and receive daily updates from their favorite
sources and communities.

## Wouldn't I need to create a lot of accounts?

No! The idea is that one use may register for <john@foobar.com> but with that sole account john may access other
Socialbox instances and interact on them without ever telling lol.com or any other foreign instance what John's
password is. For example, if <john@foobar.com> authenticates to lol.com, it's up to lol.com to verify if john is actually
john from foobar.com by talking to foobar.com directly, this way lol.com can verify that john from foobar.com is
actually john.

## License

This project is licensed under GNU Free Documentation License v1.3, see the [LICENSE](LICENSE.md) file for details.

## Table of contents

<!-- TOC -->
- [About Socialbox](#about-socialbox)
  - [What's Socialbox?](#whats-socialbox)
  - [Why use Socialbox?](#why-use-socialbox)
  - [Wouldn't I need to create a lot of accounts?](#wouldnt-i-need-to-create-a-lot-of-accounts)
  - [License](#license)
  - [Table of contents](#table-of-contents)
- [Guidelines](#guidelines)
  - [Backwards Compatibility](#backwards-compatibility)
    - [Deprecation](#deprecation)
- [Specifications](#specifications)
  - [UUID v4](#uuid-v4)
  - [DNS Records](#dns-records)
  - [Peer Address](#peer-address)
    - [User Address](#user-address)
    - [Server Address](#server-address)
    - [Reserved Usernames](#reserved-usernames)
    - [Regex Pattern (PCRE)](#regex-pattern-pcre)
  - [RPC Communication](#rpc-communication)
    - [How to host the RPC server](#how-to-host-the-rpc-server)
    - [Notification \& Request-Response Communication](#notification--request-response-communication)
    - [Request Object](#request-object)
    - [Response Object](#response-object)
    - [Error Response Object](#error-response-object)
  - [Cryptography](#cryptography)
    - [Key Generation](#key-generation)
    - [Signing and Signature Verification](#signing-and-signature-verification)
    - [Temporary Signature \& Verification](#temporary-signature--verification)
    - [Encryption and Decryption](#encryption-and-decryption)
    - [Error Handling](#error-handling)
    - [Methods](#methods)
      - [generateKeyPair()](#generatekeypair)
      - [signContent(content: String, privateKey: String): String](#signcontentcontent-string-privatekey-string-string)
      - [verifyContent(content: String, signature: String, publicKey: String): Boolean](#verifycontentcontent-string-signature-string-publickey-string-boolean)
      - [temporarySignContent(content: String, privateKey: String): String](#temporarysigncontentcontent-string-privatekey-string-string)
      - [verifyTemporarySignature(content: String, signature: String, publicKey: String, frames: Integer): Boolean](#verifytemporarysignaturecontent-string-signature-string-publickey-string-frames-integer-boolean)
      - [encryptContent(content: String, publicKey: String): String](#encryptcontentcontent-string-publickey-string-string)
      - [decryptContent(ciphertext: String, privateKey: String): String](#decryptcontentciphertext-string-privatekey-string-string)
    - [Example Implementations](#example-implementations)
- [Authentication](#authentication)
  - [First-Level Authentication](#first-level-authentication)
    - [Password (LOGIN)](#password-login)
  - [Second-Level authentication](#second-level-authentication)
    - [TOTP (Time-based One-Time Password)](#totp-time-based-one-time-password)
- [Procedures](#procedures)
  - [Establishing a connection](#establishing-a-connection)
    - [Step 1: DNS Handshake](#step-1-dns-handshake)
    - [Step 2: Establish Connection](#step-2-establish-connection)
- [Methods](#methods-1)
  - [Core](#core)
  - [Public](#public)
    - [Ping (`ping`)](#ping-ping)
  - [Protected](#protected)
  - [Internal](#internal)
- [Error Codes](#error-codes)
  - [HTTP Status Codes](#http-status-codes)
  - [-1xxx: RPC Errors](#-1xxx-rpc-errors)
  - [-2xxx: Server Errors](#-2xxx-server-errors)
<!-- TOC -->

------------------------------------------------------------------------------------------------------------------------

# Guidelines

The guideline section is used to outline guidelines that the standard & project must adhere to, these guidelines are
placed here to ensure that future generations of this specification would remain backwards compatible with at least
up to the first specification version of this project, additionally this section is meant to outline what the project
is intended to be used for and what it's not used for.

## Backwards Compatibility

This specification just like any other project out there, would undergo changes as needed, whether or not these changes
are breaking changes or not, the project must always remain backwards compatible with the first version of the project.

### Deprecation

In the case a method, procedure or object is deprecated, good servers should still continue to support these deprecated
methods, one way to do this is to allow the server to convert the deprecated method to the new method in the background
while retaining the same result as the deprecated method. To consider a method deprecated, the specification must provide
a way as explained in the deprecation comments on how to use the same method call with the newly replaced method.

------------------------------------------------------------------------------------------------------------------------

# Specifications

Specifications are used to define exactly how each part of the Socialbox standard works, from communication to privacy,
security & limitations. Servers & Clients alike are expected to follow these specification at it's core for the
best results and compatibility with other systems.

## UUID v4

Anything on the Socialbox world that needs to be uniquely identified with a random identifier must use the UUID V4
specification. UUID v4 is a randomly generated identifier that consists of 32 hexadecimal digits separated by hyphens.

> A version 4 UUID is randomly generated. As in other UUIDs, 4 bits are used to indicate version 4, and 2 or 3 bits to
indicate the variant (102 or 1102 for variants 1 and 2 respectively). Thus, for variant 1 (that is, most UUIDs) a
random version 4 UUID will have 6 predetermined variant and version bits, leaving 122 bits for the randomly generated
part, for a total of 2122, or 5.3×1036 (5.3 undecillion) possible version-4 variant-1 UUIDs. There are half as many
possible version 4, variant 2 UUIDs (legacy GUIDs) because there is one less random bit available, 3 bits being
consumed for the variant.

Source: [Wikipedia](https://en.wikipedia.org/wiki/Universally_unique_identifier#Version_4_(random))

## DNS Records

When a client wants to connect to a Socialbox server, it first needs to perform a DNS handshake to discover the server
URL. Typically, the Socialbox server is hosted on a subdomain like socialbox.example.com. To determine this, the client
must first resolve the main domain, example.com, and get a TXT record that contains the URL of the Socialbox instance.
The required TXT record should be placed in the main domain’s DNS records with this format:

```text
example.com.  IN  TXT  "socialbox=socialbox.example.com"
```

Here, socialbox is the key, and the value is the URL of the Socialbox instance. The client resolves the main domain to
retrieve the TXT record, which then provides the URL of the Socialbox server. The client uses this URL to establish a
connection to the Socialbox server. This process allows the client to dynamically discover the server URL.

The domain name is usually resolved from a given peer address.

## Peer Address

A peer address uniquely identifies a peer associated with a Socialbox instance, resembling a traditional email address
format, where a username and domain are separated by an @ symbol. Both the username and domain are case-insensitive,
and the domain must be a valid domain name. A typical peer address looks like this:

```text
john@example.com
```

If a Socialbox instance is hosted on a subdomain, such as socialbox.example.com, the peer address format does not change
and remains tied to the main domain. For example, if example.com is the main domain, a DNS TXT record should be added to
the main domain's DNS settings in the following format:

```text
example.com.  IN  TXT  "socialbox=socialbox.example.com"
```

This record indicates that the Socialbox instance is hosted on the subdomain socialbox.example.com, while the peer
address stays consistent as <john@example.com>. This is because clients always resolve the main domain to find the TXT
record, which provides the URL of the Socialbox instance.

  > TODO: Should specify username and domain name restrictions, such as length, character set, etc. (?)

### User Address

A user address is a peer address that identifies a user associated with a Socialbox instance. The user address format
consists of a username the domain name to which the user's account is registered, for example, *<john@example.com>*

### Server Address

A server address is a strict peer address that is similar a regular user address but instead the username is always
`host` and the domain name is the domain name of the server, for example, *<host@example.com>* indicates that the server
itself is the peer.

### Reserved Usernames

Certain usernames are reserved and cannot be used by users to register accounts. The following usernames are reserved:

* `host`: Reserved for server addresses.
* `admin`: Reserved for administrative purposes.
* `root`: Reserved for the root user.
* `system`: Reserved for system-related tasks.
* `anonymous`: Reserved for anonymous users.
* `guest`: Reserved for guest users.
* `support`: Reserved for support-related tasks.

### Regex Pattern (PCRE)

The following regex pattern can be used to validate a peer address:

```regex
^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
```

## RPC Communication

Socialbox employs JSON-RPC over HTTP for server-client & server-server communication. JSON-RPC is a stateless,
lightweight remote procedure call (RPC) protocol. This implementation is based on the
[JSON-RPC 2.0 specification](https://www.jsonrpc.org/specification) with certain modifications to meet the Socialbox
standards. Below are the modifications made to the JSON-RPC 2.0 specification:

* Removed the redundant `jsonrpc` field from the request object, as the protocol is already defined as JSON-RPC 2.0.
* Revised error codes to align with the Socialbox standard. Error codes are categorized by the first digit, which
  represents the error category, followed by digits indicating the specific error. For more details, refer to the
  "RPC Errors" section under [Error Codes](#error-codes).
* Request IDs use an 8-character long unique identifier instead of the regular integer. Although theoretically any
  string can be used, it is recommended to use CRC32 hex encoded strings for the request ID.
* Flattened the `error` object in the response object to include the error code and message directly under separate
  fields instead of nesting them under the `error` object.
* Utilize HTTP status codes to indicate the status of the HTTP request-response cycle. For more details, refer to the
  "HTTP Status Codes" section under [Error Codes](#error-codes).

### How to host the RPC server

To host an RPC server, you must configure your domain name to have a subdomain that serves as the RPC endpoint for your
Socialbox instance. For example, if your domain is example.com, you can host the RPC server on the subdomain
socialbox.example.com. The RPC server should be accessible via HTTPS, and the root URL should be the RPC endpoint. For
example, the client would assume the RPC endpoint URL would look like this after preforming the DNS Handshake, see
[DNS Records](#dns-records) to see how this part is configured.

```text
https://socialbox.example.com/
```

> You may use any subdomain name for the RPC endpoint, but the DNS TXT record should be placed in the main domain's DNS
  and should contain the correct subdomain of the RPC endpoint.

Sub-Endpoints are not supported, the RPC endpoint URL **should not** contain any path or query parameter such as

```text

```text
 - https://socialbox.example.com/rpc
 - https://socialbox.example.com/rpc/endpoint
 - https://socialbox.example.com/?rpc
 - https://socialbox.example.com/?api
 etc...
```

To break it down in three easy steps, say we want to talk to the server where `john@example.com` is hosted:

 1. We resolve the domain name `example.com` to get the TXT record that contains the URL of the Socialbox instance.
 2. `example.com` resolves to `socialbox.example.com` which is the RPC endpoint.
 3. We assume the RPC endpoint URL is `https://socialbox.example.com/`

### Notification & Request-Response Communication

Notification requests are requests where the request object does not contain a request ID. The server processes these
requests silently without sending a response. Notification requests are used for one-way communication where the client
does not need a response from the server.

If the client needs the results of a request, it must include a request ID in the request object. The server will then
respond with a response object containing the request ID, allowing the client to match the response with the request.

For example:

```text
SEND: {"id": "3bb935c6", "method": "subtract", "parameters": {"subtrahend": 23, "minuend": 42}}
REC: {"id": "3bb935c6", "result": 19}
```

In this example, the client requests to subtract 23 from 42 and includes a request ID in the request object. The server
processes the request and responds with the result of 19 and the request ID. The client can use the request ID to match
the response with the request.

When the client sends multiple method calls within a single request, each method call must have a unique request ID.
The server will respond with a response object for each method call containing the respective request ID and will omit
responses for requests lacking a request ID.

For example:

```text
SEND: [
  {"id": "3bb935c6", "method": "subtract", "parameters": {"subtrahend": 23, "minuend": 42}},
  {"id": "3bb935c7", "method": "add", "parameters": {"addend1": 23, "addend2": 42}},
  {"method": "multiply", "parameters": {"multiplicand": 23, "multiplier": 42}}
]
REC: [
  {"id": "3bb935c6", "result": 19},
  {"id": "3bb935c7", "result": 65}
]
```

In this example, the client sends three method calls within one request, each with a unique request ID. The server
processes the requests and responds with a response object for each method call containing its request ID. The server
omits the response for the third method call as it does not contain a request ID.

> In cases where the client sends malformed requests or the server encounters an RPC error, the server will not respond
  with an RPC error response object. Instead, the server will respond with an HTTP status code indicating the error.
  See HTTP Status Codes under [Error Codes](#error-codes) for more details.

### Request Object

A request object is a JSON object that contains the following fields:

```json
{
  "id": "3bb935c6",
  "method": "subtract",
  "parameters": {"subtrahend": 23, "minuend": 42}
}
```

The fields in the request object are as follows:

| Name         | Type     | Required | Example                             | Description                                                         |
|--------------|----------|----------|-------------------------------------|---------------------------------------------------------------------|
| `id`         | `String` | No       | `3bb935c6`                          | Optional. The request ID, if omitted the request is a notification. |
| `method`     | `String` | Yes      | subtract                            | The method to be invoked.                                           |
| `parameters` | `Array`  | No       | `{"subtrahend": 23, "minuend": 42}` | Optional. The parameters to pass.                                   |

### Response Object

A response object is a JSON object that contains the following fields:

```json
{
  "id": "3bb935c6",
  "result": 19
}
```

The fields in the response object are as follows:

| Name     | Type     | Required | Example    | Description                                            |
|----------|----------|----------|------------|--------------------------------------------------------|
| `id`     | `String` | No       | `3bb935c6` | Optional. The request ID of the corresponding request. |
| `result` | `Any`    | Yes      | 19         | The result of the method call.                         |

### Error Response Object

An error response object is a JSON object that contains the following fields:

```json
{
  "id": "3bb935c6",
  "error": "Method not found",
  "code": 0
}
```

The fields in the error response object are as follows:

| Name      | Type      | Required | Example          | Description                                            |
|-----------|-----------|----------|------------------|--------------------------------------------------------|
| `id`      | `String`  | No       | `3bb935c6`       | Optional. The request ID of the corresponding request. |
| `error`   | `String`  | Yes      | Method not found | The error message.                                     |
| `code`    | `Integer` | Yes      | 0                | The error code.                                        |


## Cryptography

Cryptography is a crucial part of the Socialbox standard. It serves many purposes such as session integrity to prevent
session hijacking, data integrity to prevent data tampering, and confidentiality to prevent data eavesdropping. Every
Socialbox client & server must implement the same cryptographic methods to ensure compatibility with other systems.
Mainly, the Socialbox standard uses the following cryptographic methods:

* **RSA**: Used for asymmetric encryption and decryption.
* **SHA256**: Used for hashing data and generating secure signatures.
* **Base64 Encoding**: All binary data (such as keys, signatures, and encrypted data) is encoded into Base64 for safe transmission.

 > Note: Base64 encoding is necessary because binary data cannot be safely transmitted in certain contexts like URLs or
   JSON. Base64 converts binary data into a text-safe format.

### Key Generation

Key generation is the process of generating cryptographic keys for encryption and decryption. In Socialbox, RSA keys are
used for asymmetric encryption and decryption. The key generation process involves generating a public key and a private
key. The public key can be shared with others to encrypt/verify data, while the private key is kept secret and used to
decrypt/sign data. These are the following conditions for key generation:

* **Algorithm**: The algorithm used for key generation must be RSA.
* **Key Size**: The key size must be 2048 bits.
* **Padding**: The padding scheme used for encryption and decryption must be OAEP (Optimal Asymmetric Encryption Padding).
* **Hash Function**: The hash function used for RSA encryption and decryption must be SHA-1.
* **Key Encoding** Base64 encoded DER format.
* **Private Key** Must be stored in Base64 encoding using [PKCS#8](https://docs.openssl.org/master/man1/openssl-pkcs8/) standard.
* **Public Key** Must be stored in Base64 encoding using [X.509](https://docs.openssl.org/master/man7/x509/) standard.

Example key generation using OpenSSL:

```bash
# Generate a private key
openssl genpkey -algorithm RSA -out private.der -pkeyopt rsa_keygen_bits:2048 -outform DER

# Extract the public key from the private key
openssl rsa -in private.der -inform DER -pubout -out public.der -outform DER

# Convert the keys to Base64 encoding (no PEM headers)
openssl base64 -in private.der -out private_base64.txt
openssl base64 -in public.der -out public_base64.txt
```

You should get two files, private_base64.txt and public_base64.txt, containing the private and public keys, respectively, 
in Base64 encoding without PEM headers.

```text
# private_base64.txt
MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKg...

# public_base64.txt
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQ...
```

### Signing and Signature Verification

Signing is the process of generating a digital signature for a message using a private key. The signature can be verified
by others using the corresponding public key to ensure the message's integrity and authenticity. In Socialbox, signing
and signature verification are used to ensure the integrity of data exchanged between peers.

* **Algorithm**: RSA with SHA256 hash function (SHA256withRSA)
* **Padding**: PKCS#1 v1.5 padding for signatures.
* **Input**: UTF-8 encoded string as the content to be signed.
* **Output**: Base64 encoded signature.

Example signing and signature verification using OpenSSL:

```bash
# Decode the Base64 private key to DER format
openssl base64 -d -in private_base64.txt -out private.der

# Sign the data using the DER-formatted private key
echo -n "Hello, World!" | openssl dgst -sha256 -sign private.der -out signature.bin

# Decode the Base64 public key to DER format
openssl base64 -d -in public_base64.txt -out public.der

# Verify the signature using the DER-formatted public key
echo -n "Hello, World!" | openssl dgst -sha256 -verify public.der -signature signature.bin

# Output: Verified OK
```

 > Note: In this example, the produced signature is binary data, but if you want to transmit the signature over the
   network, you must encode it using Base64 encoding.

### Temporary Signature & Verification

Temporary signatures work similarly to regular signatures, but the keypair used to sign the data is temporary and only
valid for a limited time (typically 60 seconds). This feature ensures the integrity of data exchanged between peers
within a short time window, adding protection against replay attacks. To ensure time synchronization, developers should
use NTP (Network Time Protocol).

* **Algorithm**: RSA with SHA256 hash function (SHA256withRSA)
* **Padding**: PKCS#1 v1.5 for signatures.
* **Time Limit**: The signature must be verified within X seconds.
* **Input**: UTF-8 encoded string as the content, plus the current timestamp divided by the time block.
* **Output**: Base64-encoded signature with the time component included.

Implementation example, take these parameters for example

* `content`: (String) The data to sign
* `signature` (String) The signature to verify
* `publicKey` (String) The public key to verify the signature
* `frames` (Integer) The number of frames the signature is valid for, by default the value is `1`

Time-blocks are calculated by dividing the current Unix timestamp by 60 seconds and rounding it down to the nearest
integer. For example, If the current Unix timestamp is `1725903098`, to calculate the time block we divide it by 60 
seconds and round it down to the nearest integer, the result is `28765051`, frames is the number of frames the signature
is valid for before it,  for example, if the signature is valid for 60 seconds, the frames would be `1`. If the frame
value is `2`, the signature is valid for 120 seconds, and so on.

```python
import time

def verify_temporary_signature(content, signature, publicKey, frames=1):
    # Calculate the time block
    timeBlock = int(time.time() / 60)

    # Verify the signature
    for i in range(frames):
        # Generate the temporary signature
        tempSignature = sign(content + str(timeBlock - i))

        # Verify the temporary signature
        if verify(tempSignature, publicKey, content + str(timeBlock - i)):
            return True

    return False
```

For the rest of the signature process, remains normal; the only difference is that the content is appended with the
time block separated by a `|` character, for example:

```text
{content}|{timeBlock}
```

or in the example above:

```text
Hello, World!|28765051
```


### Encryption and Decryption

Encryption is the process of converting plaintext data into ciphertext using a public key, while decryption converts
ciphertext back into plaintext using the corresponding private key. In Socialbox, encryption and decryption ensure the
confidentiality of data exchanged between peers.

* **Algorithm**: RSA with OAEP (Optimal Asymmetric Encryption Padding)
* **Hash**: SHA-1 (Note: Previously, SHA-256 was specified, but for compatibility with OpenSSL, SHA-1 is used).
* **Input**: UTF-8 encoded string as the content to be encrypted.
* **Output**: Base64 encoded ciphertext.

Example encryption and decryption using OpenSSL:
  
```bash
# Encrypt the data
echo -n "Hello, World!" | openssl rsautl -encrypt -oaep -pubin -inkey public_base64.txt -out ciphertext.bin

# Decrypt the data
openssl rsautl -decrypt -oaep -inkey private_base64.txt -in ciphertext.bin


```

 > Note: In this example, the produced ciphertext is binary data, but if you want to transmit the ciphertext over the
   network, you must encode it using Base64 encoding.
 >

### Error Handling

For real-world implementations, error handling should be a priority. For example, signature verification and decryption
can fail if the data is tampered with, keys don’t match, or the data has expired. Ensure that invalid signatures or
decryption errors are caught and handled appropriately to avoid security vulnerabilities

### Methods

The following methods should be implemented by all Socialbox servers and clients to ensure compatibility with other.

#### generateKeyPair()

![generateKeyPair Diagram](images/generateKeyPair.png "generateKeyPair Diagram")
Generates a new RSA key pair for encryption and decryption, returning the public and private keys in Base64 encoding.

#### signContent(content: String, privateKey: String): String

![signContent Diagram](images/signContent.png "signContent Diagram")
Signs the content using the private key and returns the signature in Base64 encoding.
The content is expected to be a UTF-8 encoded string.

#### verifyContent(content: String, signature: String, publicKey: String): Boolean

![verifyContent Diagram](images/verifyContent.png "verifyContent Diagram")
Verifies the signature of the content using the public key and returns true if the signature is valid, false otherwise.

#### temporarySignContent(content: String, privateKey: String): String

![temporarySignContent Diagram](images/temporarySignContent.png "temporarySignContent Diagram")
Signs the content using a temporary private key and returns the temporary signature in Base64 encoding.

#### verifyTemporarySignature(content: String, signature: String, publicKey: String, frames: Integer): Boolean

![verifyTemproarySignature Diagram](images/verifyTemproarySignature.png "verifyTemporarySignature")
Verifies the temporary signature of the content using the public key and returns true if the signature is valid
within the specified time frame.

#### encryptContent(content: String, publicKey: String): String

![encryptContent Diagram](images/encryptContent.png "encryptContent Diagram")
Encrypts the content using the public key and returns the ciphertext in Base64 encoding.

#### decryptContent(ciphertext: String, privateKey: String): String

![decryptContent Diagram](images/decryptContent.png "decryptContent Diagram")
Decrypts the ciphertext using the private key and returns the plaintext content.

### Example Implementations

This standard provides examples of how to implement the cryptographic methods using OpenSSL or any other cryptographic
library that supports RSA encryption and decryption. The examples demonstrate how to generate RSA key pairs, sign and
verify content, and encrypt and decrypt data using RSA.

 > Note: The examples provided are for demonstration purposes only. Developers should use a secure cryptographic library
   and follow best practices to ensure the security of their implementations.
 
 - [Python](examples/cryptography.py)
 - [Java](examples/Cryptography.java)
 - [PHP](examples/cryptography.php)
 - [C](examples/cryptography.c)

------------------------------------------------------------------------------------------------------------------------

# Authentication

The Socialbox standard strives to be as flexiable as it can be, servers may implement all or some of the authentication
methods described in this section. But a client must be expected to be able to handle all of these authentication methods
to ensure compatibility with all servers.

Authentication procedures are seperated to two levels, the first level is the initial authentication level where the user
must use to at least authenticate to the server

 > TODO: Object structures must be defined & the authentication process must be explained

## First-Level Authentication

A first level authentication is always the first and initial method of auhthentication that the user can preform, there
are multiple ways to handle authentication in the first-level but essentially this is the first step the user must take.

### Password (LOGIN)

The most common way to authenticate a user is by using a password, the user must provide their password to authenticate
to the server. The password must be hashed using `SHA512`. The server must be able to verify if the given hash of the
password is correct.


## Second-Level authentication

A second level authentication is optional, this is what the server may ask the client to provide for additional security,
second-level authentication is usually reserved for a two-step verification process if the user has enabled it and if or
when the server requires it.

### TOTP (Time-based One-Time Password)

Time-based One-Time Password (TOTP) is a second-level authentication method that generates a one-time password based on
a shared secret key and the current time. The server and client must share a secret key to generate the one-time password.
The client generates the one-time password using the secret key and the current time, which the server can verify to
authenticate the user.

------------------------------------------------------------------------------------------------------------------------


# Procedures

Procedures as described in the standard are methods that a server & client must implement to ensure compatibility with
other systems. These procedures are the core of the Socialbox standard and are required to be implemented by all
Socialbox servers and clients, these procedures can range from how an connection is established to how a user is
authenticated or how encryption is handled.

## Establishing a connection

When a client wants to connect to a Socialbox server, it must first perform a DNS handshake to discover the server URL.
For this example, let's assume the server is hosted on the subdomain socialbox.example.com. The client identified as
the peer `john@example.com` is trying to connect to the server to authenticate to it or even register an account if
john doesn't have one.

### Step 1: DNS Handshake

The client takes the peer's address and extracts the domain name, in this case, `example.com`. The client then resolves
the domain name to retrieve the TXT record that contains the URL of the Socialbox instance. The TXT record should be
placed in the main domain's DNS records with the following format:

```text
example.com.  IN  TXT  "socialbox=socialbox.example.com"
```

For more details on the DNS handshake, refer to the [DNS Records](#dns-records) section under Specifications.
Now we figured out that the Socialbox instance RPC endpoint is found at `https://socialbox.example.com/`.

 1. Client always assumes SSL/TLS is enabled, so the client will always connect to the server using HTTPS.
 2. CLient always assumes the RPC endpoint URL is the root URL of the server, so all requests will be sent to the root
    URL of the server.

### Step 2: Establish Connection

 > TODO: To be written

------------------------------------------------------------------------------------------------------------------------

# Methods

Methods are seperated into three categories that servers could or must implement, the category type dictates this.

| Category    | Server Required | Client Required | Description                                                                                                           |
|-------------|-----------------|-----------------|-----------------------------------------------------------------------------------------------------------------------|
| `core`      | Yes             | Yes             | Core methods are required to be implemented by all servers and clients.                                               |
| `public`    | Yes             | Yes             | Public methods are methods that are available to all users without authentication.                                    |
| `protected` | Yes             | Yes             | Protected methods are methods that requires authentication to access them.                                            |
| `internal`  | No              | No              | Internal methods are methods reserved for administrative operations to the server if the peer is allowed to use them. |

To break down these categories in more detail, this section is going to describe their purposes:

## Core

Core methods are methods that are required to be implemented by all servers and clients. These methods are essential
and may include methods for authentication, registration, and other core functionalities. Core methods are used to
establish a connection between the client and server and are necessary for the client to interact with the server.

## Public

Public methods are methods that are available to all peers without authentication, meaning that any peer can access.

### Ping (`ping`)

Ping allows you to test the connection to the server, this method doesn't accept any parameters and only returns
`true` as the result

 > Returns: Boolean (true)

RPC Example:

```text
SEND: {"id": "3bb935c6", "method": "ping"}
REC: {"id": "3bb935c6", "result": true}
```

## Protected

Public methods are the opposite of public methods, these methods require authentication to access them. These methods
are used to perform operations that require the peer to be authenticated, such as posting messages, creating communities,
and other operations related to the peer's account or peer's interactivity with the server.

## Internal

Internal methods are optional, restricted functions that enable a peer to perform administrative tasks on the server.
These methods require authentication, and it's up to the server to determine if the authenticated peer has the necessary
permissions to carry out administrative operations. If the server offers an alternative way for administrators to manage
it, these methods should remain entirely optional.

------------------------------------------------------------------------------------------------------------------------

# Error Codes

Error codes are globally defined codes that represent the type of error that occurred during a method call. The error
codes are categorized by the first digit, which represents the error category, followed by digits indicating the specific
error. The following are the error categories and their respective error codes:

## HTTP Status Codes

HTTP status codes indicate the status of the HTTP request-response cycle. These response codes do not reflect the status
of the method call(s) but rather the status of the request or response itself, independent of the method call(s).

The client should first check the HTTP status code before parsing the response body. If the status code is not 200,
the client should not parse the response body, as it will contain a non-JSON encoded error message. For example,
if the status code is 400, the response body will contain a message like "Bad Request," which the client should
display to the user as the error message.

| Code | Status       | Description                                                                            |
|------|--------------|----------------------------------------------------------------------------------------|
| 200  | OK           | The RPC request was successful.                                                        |
| 400  | Bad Request  | The RPC request was invalid or missing required fields.                                |
| 500  | Server Error | An internal server error occurred during the RPC process or the server is unavailable. |

## -1xxx: RPC Errors

RPC errors are errors that occur during the remote procedure call (RPC) process. These errors are related to the
communication between the client and server and the method invocation process.

| Code  | Reason             | Description                                                                 |
|-------|--------------------|-----------------------------------------------------------------------------|
| -1000 | Invalid Request    | The request object is invalid or missing required fields.                   |
| -1001 | Method not found   | The requested method does not exist on the server.                          |
| -1002 | Invalid Parameters | The parameters passed to the method are invalid or missing required fields. |

## -2xxx: Server Errors

Server errors are errors that occur on the server-side during the method invocation process.

| Code  | Reason             | Description                                                                                       |
|-------|--------------------|---------------------------------------------------------------------------------------------------|
| -2000 | Internal Error     | An internal server error occurred during the method invocation process.                           |
| -2001 | Server Unavailable | The server is unavailable and cannot process the request, usually due to maintenance or downtime. |
