// FUNC_NAME: GameEntity::GameEntity
// Address: 0x006ae790
// Constructor for a game entity that optionally allocates an internal data block (0x2c0 bytes) based on a flag.

void __thiscall GameEntity::GameEntity(byte flags) {
    // Call base class constructor
    BaseEntity::initialize(this);

    // If bit 0 of flags is set, allocate the internal resource of size 0x2c0 (704 bytes)
    if ((flags & 1) != 0) {
        allocateMemoryBlock(this, 0x2c0);
    }
}