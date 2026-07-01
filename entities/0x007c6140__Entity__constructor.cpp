// FUNC_NAME: Entity::constructor
// Address: 0x007c6140
// Role: Initializes an Entity object, with an optional setup step based on a flag.

// The function calls a base initialization routine, then if the low bit of 'flags'
// is set, it calls a secondary setup (likely for network replication or persistent state).

Entity * __thiscall Entity::constructor(Entity *this, byte flags)
{
    // Common base initialization (zeroes memory, sets default values)
    Entity::initBase();

    // If the 0x01 bit is set, perform additional configuration.
    // This is often used to distinguish between local and networked objects,
    // or to register the object with a manager.
    if ((flags & 1) != 0) {
        Entity::finalize(this);
    }

    return this;
}