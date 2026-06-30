// FUNC_NAME: Entity::constructor
// Address: 0x00570d00
// Role: Constructor for Entity class, takes an owning flag.
// If the owning flag (bit 0 of param_2) is set, calls a cleanup/destructor function.

undefined4 __thiscall Entity::constructor(Entity *this, byte owningFlag)
{
    // Call base class constructor (likely Object or EARSObject)
    // Address: 0x00581a70
    Object::constructor(this);

    // If the owning flag indicates that this object owns its memory (e.g., allocated with new),
    // call a cleanup function that may free internal resources or delete the object.
    // Address: 0x009c8eb0
    if ((owningFlag & 1) != 0) {
        Entity::cleanup(this);  // or destructor-like function
    }

    return this;
}