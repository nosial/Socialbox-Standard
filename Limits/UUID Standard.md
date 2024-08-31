The UUID Standard used in Socialbox will almost always be version 4 (Random), see below

---

A version 4 UUID is randomly generated. As in other UUIDs, 4 bits are used to indicate version 4, and 2 or 3 bits to indicate the variant (102 or 1102 for variants 1 and 2 respectively). Thus, for variant 1 (that is, most UUIDs) a random version 4 UUID will have 6 predetermined variant and version bits, leaving 122 bits for the randomly generated part, for a total of 2122, or 5.3×1036 (5.3 [undecillion](https://en.wikipedia.org/wiki/Names_of_large_numbers "Names of large numbers")) possible version-4 variant-1 UUIDs. There are half as many possible version 4, variant 2 UUIDs (legacy GUIDs) because there is one less random bit available, 3 bits being consumed for the variant.

Per [RFC](https://en.wikipedia.org/wiki/RFC_(identifier) "RFC (identifier)") [9562](https://datatracker.ietf.org/doc/html/rfc9562), the seventh octet's most significant 4 bits indicate which version the UUID adheres to. This means that the first hexadecimal digit in the third group always starts with a `4` in UUIDv4s. Visually, this looks like this `xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx`, where `M` is the UUID version field. The upper two or three bits of digit `N` encode the variant. For example, a random UUID version 4, variant 2 could be `8D8AC610-566D-4EF0-9C22-186B2A5ED793`.[[19]](https://en.wikipedia.org/wiki/Universally_unique_identifier#cite_note-19)

Source: [Universally unique identifier - Wikipedia](https://en.wikipedia.org/wiki/Universally_unique_identifier#Version_4_(random))