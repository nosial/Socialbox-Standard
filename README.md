This project is the Socialbox standard documentation, this project is intended to describe the standard for which Socialbox servers and clients would use to communicate over the internet.

## What's Socialbox?

Socialbox is a decentralized platform for hosting social media instances, enabling users to register/authenticate on various instances and communicate with other users or communities across different instances without relying on a centralized server. This model aims to replace traditional services like Email, Reddit, and Twitter, allowing users to create communities for private, internal, or public purposes and engage in peer-to-peer communication, even if they are on different servers.

![[decenteralized.png]]

![[peer2peer.png]]

## Why use Socialbox?

Email has been around for a long time, but it only allows us to send messages to each other but it's still great, because it allows *Alice* from example.com to send an email to `John` at foobar.com even if both users are on different servers with possibility of different features, but the underlying protocol still works to allow two users from different servers to communicate with each other.

But take Twitter or Reddit for example, users are constrained to creating their accounts or boards on that one and only platform, if Reddit or anyone on that platform doesn't like that board, they could very well take it down and make it inaccessible to many users. Even worse if Reddit goes down entirely! Socialbox aims to fix this to allow users to explore the internet as it once was without being tied to a centralized service, so for example john@foobar.com may be able to post on cats@lol.com and interact with other users that doesn't necessarily come from lol.com or foobar.com. john@foobar.com may also subscribe to these channels and or boards and receive daily updates from their favorite sources and communities.

## Wouldn't i need to create a lot of accounts?

No! The idea is that one use may register for john@foobar.com but with that sole account john may access other Socialbox instances and interact on them without ever telling lol.com or any other foreign instance what John's password is. For example, if john@foobar.com authenticates to lol.com, it's up to lol.com to verify if john is actually john from foobar.com by talking to foobar.com directly, this way lol.com can verify that john from foobar.com is actually john.

---
## License

 Copyright (C) 2024 Socialbox Team
 Copyright (C) 2022-2024 Nosial Technologies
  
    Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
    or any later version published by the Free Software Foundation;
    with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
    A copy of the license is included in the section entitled "GNU
    Free Documentation License".

See [[LICENSE]] for more details.