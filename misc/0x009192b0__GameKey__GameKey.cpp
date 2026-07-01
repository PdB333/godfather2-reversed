// FUNC_NAME: GameKey::GameKey
// Function address: 0x009192b0
// Role: Constructor for a GameKey object, storing an ID and a 64-bit hash value.
// Structure:
//   +0x00: vtable pointer
//   +0x04: ID (4 bytes)
//   +0x08: hash (8 bytes)
//   +0x10: padding (8 bytes, not used after initialization)

void __thiscall GameKey::GameKey(GameKey* this, uint32_t id, uint64_t hash)
{
    this->vtable = (void**)(&LAB_00917910);  // Initialize vtable
    this->id = id;                           // Store ID
    this->hash = 0;                          // Clear hash
    *(uint64_t*)((uint8_t*)this + 0x10) = 0; // Clear padding
    this->hash = hash;                       // Set final hash
}