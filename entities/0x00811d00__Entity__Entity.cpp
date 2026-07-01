// FUNC_NAME: Entity::Entity
// Constructor for Entity class. Calls base class constructor and optionally allocates extra data buffer of size 0xF0.
// param_1: this pointer (implicit)
// param_2: flags byte; bit 0 indicates whether to allocate extra data buffer
Entity* __thiscall Entity::Entity(Entity* this, byte flags)
{
    // Call base class constructor (likely BaseEntity or EARSObject)
    BaseEntity::BaseEntity();

    // If bit 0 of flags is set, allocate an extra data buffer of 0xF0 bytes
    if ((flags & 1) != 0) {
        // FUN_0043b960 is likely a custom allocator or placement new for the extra data
        // It takes this pointer and size 0xF0, possibly initializing a member pointer
        AllocateExtraData(this, 0xF0);
    }

    return this;
}