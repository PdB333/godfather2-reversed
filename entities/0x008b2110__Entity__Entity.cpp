// FUNC_NAME: Entity::Entity
// Address: 0x008b2110
// Reconstructed constructor for Entity class. Takes a flags byte, with bit 0 controlling additional initialization (likely dynamic allocation or deferred setup).
Entity* __thiscall Entity::Entity(Entity* this, byte flags) {
    // Call base class constructor (BaseObject or SimObject) at 0x008b1eb0
    BaseObject::BaseObject(this);

    // If the low bit of flags is set, perform extra initialization (e.g., allocate dynamic data)
    if (flags & 1) {
        // Member function at 0x009c8eb0; handles additional setup
        Entity::initWithFlag(this);
    }

    return this;
}