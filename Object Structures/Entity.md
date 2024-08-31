The Entity object can be used to represent a entity such as a User, Bot or anything to mimic a sender or receiver.

---

 - `uuid`: (**String**) *The Unique Universal Identifier of the entity, see [[UUID Standard]] for how the UUID should be structured*
 - `type`: (**Enum**) *The Enum value of the entity type*
	 - `USER`: *This represents a user account on the instance*
	 - `BOT`: *This represents a bot account managed by a user on the instance*
	 - `CHANNEL`: *This represents a channel that the user can subscribe and or post as.*
- `username`: (**String**): *This represents the unique username under the domain*
- `domain`: (**String**): *This represents the domain the entity is under*
 - `display_name`: (**String**) *The display name of the entity*