// FUNC_NAME: PlayerManager::PlayerManager
// Constructor at 0x00476100 for a player management class (likely part of EA EARS engine).
// Calls base class constructor at 0x0046c590, then initializes multiple fields including vtable pointers
// and a table of 8 player indices set to -1 (invalid).
// Offsets are given as (int*) indices (each int = 4 bytes).

PlayerManager * __thiscall PlayerManager::PlayerManager(PlayerManager *this, uint32_t param) {
    // Call base class constructor (likely EARSObject or similar)
    BaseClassConstructorFunc(param); // FUN_0046c590(param)

    // Set vtable pointers – this object appears to have multiple virtual function tables
    // (possibly a derived class with multiple inheritance or runtime type info)
    this->vtablePtrA = &PTR_TABLE_A;           // +0x00: primary vtable pointer
    *reinterpret_cast<int **>(this) = &PTR_FUNC_TABLE_ENTRY; // Actually *this = vtable entry, but above already set? Reexamine: *param_1 = &PTR_FUN_00e32e84; likely sets first vtable entry function pointer.
    this->vtablePtrB = &PTR_TABLE_B;           // +0x3C (offset 0x0F)
    this->vtablePtrC = &PTR_TABLE_C;           // +0x48 (offset 0x12)
    this->vtablePtrD = &PTR_TABLE_D;           // +0x50 (offset 0x14) – overwrites previous vtablePtrA? Possibly separate.
    this->field14 = 0;                         // +0x54 (offset 0x15)
    *reinterpret_cast<uint16_t *>(&this->field15) = 0; // +0x58 (offset 0x16)
    *reinterpret_cast<uint16_t *>(reinterpret_cast<uint8_t *>(this) + 0x5A) = 0; // +0x5C (offset 0x5A)
    this->field17 = 0;                         // +0x5C (offset 0x17)
    *reinterpret_cast<uint16_t *>(&this->field18) = 0; // +0x60 (offset 0x18)
    *reinterpret_cast<uint16_t *>(reinterpret_cast<uint8_t *>(this) + 0x62) = 0; // +0x64 (offset 0x62)
    this->field1A = 0;                         // +0x68 (offset 0x1A)
    this->field19 = 0;                         // +0x64 (offset 0x19)
    this->field1B = 0;                         // +0x6C (offset 0x1B)

    // Initialize an array of 8 player indices to -1 (invalid)
    // Offsets: 0x1C,0x1E,0x20,0x22,0x24,0x26,0x28,0x2A (each is an int)
    this->playerIndices[0] = -1; // +0x70
    this->playerIndices[1] = -1; // +0x78
    this->playerIndices[2] = -1; // +0x80
    this->playerIndices[3] = -1; // +0x88
    this->playerIndices[4] = -1; // +0x90
    this->playerIndices[5] = -1; // +0x98
    this->playerIndices[6] = -1; // +0xA0
    this->playerIndices[7] = -1; // +0xA8

    // Zero out additional fields interspersed (possibly alignment or flags)
    this->field1D = 0; // +0x74
    this->field1F = 0; // +0x7C
    this->field21 = 0; // +0x84
    this->field23 = 0; // +0x8C
    this->field25 = 0; // +0x94
    this->field27 = 0; // +0x9C
    this->field29 = 0; // +0xA4

    return this;
}