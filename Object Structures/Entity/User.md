The user object is used for storing basic information about the user, authentication details are not stored on this table. Instead it would be a foreign reference key for the available authentication types that this user can use.

This object extends [[Entity]] to represent an entity.

----

## Structure
 - `uuid` (**String**): *The Unique Universal Identifier for the user object* #unique #primary_key #indexed This extends [[Entity]]
 - `type` (Enum): The entity type, for users it's always `USER`. This extends [[Entity]]
 - `username` (**String**): *The Unique username associated with the user* #unique #paired_index (with `domain`) #indexed. This extends [[Entity]]
 - `domain` (**String**): *The domain to which this user is associated with, by default `LOCAL` for users created under the server's local domain.* (==This server manages this user==) #paired_index #indexed This extends [[Entity]]
	 `username` and `domain` are paired unique indexes, which means the username `John` may exist under `LOCAL` but uniquely, no other user under `LOCAL` can claim this username; but someone else from `example.com` may claim the username `John` so that `john@localhost` and `john@example.com` are always unique pairs per server instance
 - `display_name`: (**String**) *The display name for the user, non-unique.
 - `anonymous`: (Boolean) Indicates if this user account is temporary & anonymous
 - `created`: (Timestamp) *The Timestamp for when this account was created*