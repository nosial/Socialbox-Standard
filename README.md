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
explore the internet as it once was without being tied to a centralized service, so for example john@foobar.com may be
able to post on cats@lol.com and interact with other users that doesn't necessarily come from lol.com or foobar.com.
john@foobar.com may also subscribe to these channels and or boards and receive daily updates from their favorite
sources and communities.

## Wouldn't I need to create a lot of accounts?

No! The idea is that one use may register for john@foobar.com but with that sole account john may access other
Socialbox instances and interact on them without ever telling lol.com or any other foreign instance what John's
password is. For example, if john@foobar.com authenticates to lol.com, it's up to lol.com to verify if john is actually
john from foobar.com by talking to foobar.com directly, this way lol.com can verify that john from foobar.com is
actually john.

## License

This project is licensed under GNU Free Documentation License v1.3, see the [LICENSE](LICENSE.md) file for details.


## Table of contents

<!-- TOC -->
* [About Socialbox](#about-socialbox)
  * [What's Socialbox?](#whats-socialbox)
  * [Why use Socialbox?](#why-use-socialbox)
  * [Wouldn't I need to create a lot of accounts?](#wouldnt-i-need-to-create-a-lot-of-accounts)
  * [License](#license)
  * [Table of contents](#table-of-contents)
* [Specifications](#specifications)
  * [UUID v4](#uuid-v4)
  * [RPC Communication](#rpc-communication)
    * [Notification & Request-Response Communication](#notification--request-response-communication)
    * [Request Object](#request-object)
    * [Response Object](#response-object)
    * [Error Response Object](#error-response-object)
* [Error Codes](#error-codes)
  * [-1xxx: RPC Errors](#-1xxx-rpc-errors)
  * [-2xxx: Server Errors](#-2xxx-server-errors)
<!-- TOC -->

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


## RPC Communication

Socialbox employs JSON-RPC over HTTP for server-client & server-server communication. JSON-RPC is a stateless,
lightweight remote procedure call (RPC) protocol. This implementation is based on the JSON-RPC 2.0 specification
with certain modifications  to meet the Socialbox standards. Below are the modifications made to the JSON-RPC 2.0
specification:

- Removed the redundant `jsonrpc` field from the request object, as the protocol is already defined as JSON-RPC 2.0.
- Revised error codes to align with the Socialbox standard. Error codes are categorized by the first digit, which
  represents the error category, followed by digits indicating the specific error. For more details, refer to the
  "RPC Errors" section under [Error Codes](#error-codes).
- Request IDs use an 8-character long unique identifier instead of the regular integer. Although theoretically any
  string can be used, it is recommended to use CRC32 hex encoded strings for the request ID.
- Flattened the `error` object in the response object to include the error code and message directly under separate
  fields instead of nesting them under the `error` object.

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


# Error Codes

Error codes are globally defined codes that represent the type of error that occurred during a method call. The error
codes are categorized by the first digit, which represents the error category, followed by digits indicating the specific
error. The following are the error categories and their respective error codes:

## -1xxx: RPC Errors

RPC errors are errors that occur during the remote procedure call (RPC) process. These errors are related to the
communication between the client and server and the method invocation process.

| Code  | Error Message      | Description                                                                 |
|-------|--------------------|-----------------------------------------------------------------------------|
| -1000 | Invalid Request    | The request object is invalid or missing required fields.                   |
| -1001 | Method not found   | The requested method does not exist on the server.                          |
| -1002 | Invalid Parameters | The parameters passed to the method are invalid or missing required fields. |


## -2xxx: Server Errors

Server errors are errors that occur on the server-side during the method invocation process.

| Code  | Error Message      | Description                                                                                       |
|-------|--------------------|---------------------------------------------------------------------------------------------------|
| -2000 | Internal Error     | An internal server error occurred during the method invocation process.                           |
| -2001 | Server Unavailable | The server is unavailable and cannot process the request, usually due to maintenance or downtime. |

