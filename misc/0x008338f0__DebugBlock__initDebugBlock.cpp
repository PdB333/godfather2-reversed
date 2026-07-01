// FUNC_NAME: DebugBlock::initDebugBlock
// Constructor/initializer for a debug object, filling memory with known magic constants for corruption detection.
// Structure size: at least 0x7C bytes (124 bytes).
struct DebugBlock {
    // +0x00: int field0; // 0
    // +0x04: int field1; // 0
    // +0x08: int field2; // 0
    // +0x0C: int field3; // 0
    // +0x10: unsigned int magic1; // 0xbadbadba
    // +0x14: unsigned int magic2; // 0xbeefbeef
    // +0x18: unsigned int magic3; // 0xeac15a55
    // +0x1C: unsigned int magic4; // 0x91100911
    // +0x20: unsigned int magic1; // 0xbadbadba (repeat)
    // +0x24: unsigned int magic2; // 0xbeefbeef
    // +0x28: unsigned int magic3; // 0xeac15a55
    // +0x2C: unsigned int magic4; // 0x91100911
    // +0x30: int fieldC; // 0 (set later)
    // +0x34: int fieldD; // 0 (set later)
    // +0x38: unsigned int magic1; // 0xbadbadba (third block)
    // +0x3C: unsigned int magic2; // 0xbeefbeef
    // +0x40: unsigned int magic3; // 0xeac15a55
    // +0x44: unsigned int magic4; // 0x91100911
    // +0x48: int count; // 5
    // +0x4C: int data0; // 0
    // ... (fields 0x13 to 0x1b zero)
    // +0x70: int capacity; // 0x1e (30)
    // +0x74: unsigned char byte74; // 0
    // +0x78: int field1E; // 0
};

void __fastcall DebugBlock::initDebugBlock(DebugBlock* this) {
    this->field0 = 0;
    this->field1 = 0;
    this->field2 = 0;
    this->field3 = 0;

    // Magic block 1 (offsets 0x10-0x1C)
    this->magic1 = 0xbadbadba;
    this->magic2 = 0xbeefbeef;
    this->magic3 = 0xeac15a55;
    this->magic4 = 0x91100911;

    // Magic block 2 (offsets 0x20-0x2C)
    *(unsigned int*)((char*)this + 0x20) = 0xbadbadba;
    *(unsigned int*)((char*)this + 0x24) = 0xbeefbeef;
    *(unsigned int*)((char*)this + 0x28) = 0xeac15a55;
    *(unsigned int*)((char*)this + 0x2C) = 0x91100911;

    // Magic block 3 (offsets 0x38-0x44)
    *(unsigned int*)((char*)this + 0x38) = 0xbadbadba;
    *(unsigned int*)((char*)this + 0x3C) = 0xbeefbeef;
    *(unsigned int*)((char*)this + 0x40) = 0xeac15a55;
    *(unsigned int*)((char*)this + 0x44) = 0x91100911;

    // Set count to 5 (offset 0x48)
    this->count = 5;

    // Zero fill fields from 0x4C to 0x6C (index 0x13 to 0x1b)
    for (int i = 0x13; i <= 0x1b; ++i) {
        *(int*)((char*)this + i * 4) = 0;
    }

    // Capacity = 30 (offset 0x70)
    this->capacity = 0x1e; // 30

    // Byte at offset 0x74 = 0
    *(unsigned char*)((char*)this + 0x74) = 0;

    // Field at offset 0x78 = 0
    this->field1E = 0;

    // Set fields at offsets 0x34 and 0x30 to 0 (overwrite any previous data)
    this->fieldD = 0;
    this->fieldC = 0;
}