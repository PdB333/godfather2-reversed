// FUNC_NAME: Entity::Entity
// Function address: 0x008108d0
// Constructor for Entity class. The byte parameter is a flag (bit 0 triggers memory allocation of size 0xF0).
undefined4 __thiscall Entity::Entity(Entity *this, byte flags) {
    // Call base class constructor or global initialization routine
    initialize();
    if (flags & 1) {
        // Allocate memory block of size 0xF0 (240 bytes) for this object
        allocateMemory(this, 0xF0);
    }
    return this;
}