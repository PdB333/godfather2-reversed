// FUNC_NAME: GameStateConnector::constructor
// Address: 0x004944e0
// Role: Constructor for a game state connector object (likely part of EA EARS network layer)
// Sets vtable pointer, zeroes various state fields, and clears a 64-byte buffer (probably packet or ghost data)
void GameStateConnector::constructor(void)
{
    // Call base class constructor (sets base vtable and initializes base fields)
    BaseClass::constructor();

    // Set vtable pointer to derived class vtable
    this->vtable = &VTable_GameStateConnector; // PTR_LAB_00e34dd0

    // Zero out member fields at known offsets
    this->field_0x70 = 0;   // +0x70: likely some count or flag
    this->field_0x78 = 0;   // +0x78: byte (maybe a bool or small state)
    this->field_0x79 = 0;   // +0x79: byte
    this->field_0x8c = 0;   // +0x8c: int (sequence number or time)
    this->field_0x94 = 0;   // +0x94: int (another counter)

    // Clear a 64-byte buffer starting at offset 0x7c (used for packet data or ghost snapshot)
    memset(reinterpret_cast<uint8_t*>(this) + 0x7c, 0, 0x40);

    // Zero out 8-byte fields (possibly two 32-bit values each)
    // These stores may overlap with the memset region, but are kept for clarity
    *(uint64_t*)(reinterpret_cast<uint8_t*>(this) + 0x90) = 0; // +0x90: likely a double-word state
    *(uint64_t*)(reinterpret_cast<uint8_t*>(this) + 0x92) = 0; // +0x92: another field (overlap warning)
    *(uint64_t*)(reinterpret_cast<uint8_t*>(this) + 0x98) = 0; // +0x98: double-word
    *(uint64_t*)(reinterpret_cast<uint8_t*>(this) + 0x9a) = 0; // +0x9a: another field (overlap warning)

    return;
}