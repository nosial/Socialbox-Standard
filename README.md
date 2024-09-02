# About Socialbox

This project is the Socialbox standard documentation, this project is intended to describe the standard for which
Socialbox servers and clients would use to communicate over the internet.

## What's Socialbox?

Socialbox is a decentralized platform for hosting social media instances, enabling users to register/authenticate on
various instances and communicate with other users or communities across different instances without relying on a
centralized server. This model aims to replace traditional services like Email, Reddit, and Twitter, allowing users
to create communities for private, internal, or public purposes and engage in peer-to-peer communication, even if
they are on different servers.

![decentralized.png](images%2Fdecentralized.png)
![peer2peer.png](images%2Fpeer2peer.png)

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

To be completed...