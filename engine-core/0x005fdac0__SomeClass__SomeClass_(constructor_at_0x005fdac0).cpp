// FUNC_NAME: SomeClass::SomeClass (constructor at 0x005fdac0)

// Reconstructed constructor for an EA EARS engine object.
// Initializes a large structure (approx 0x4f * 4 = 0x13C bytes) to zero,
// sets function pointers at offsets +0x28 and +0x2a to handlers,
// sets a size/buffer flag at +0x45 to 0x9000 (likely a buffer size or capability mask),
// and safely deletes any previously allocated sub-object at offset +0x44 before re‑initializing.

undefined4* SomeClass::SomeClass(SomeClass* this)
{
    // Initially zero the sub‑object pointer (will be cleaned up later)
    this->m_pSubObject = 0;          // +0x44 (index 0x11)
    this->field_0x48 = 0;            // +0x48
    this->field_0x4C = 0;            // +0x4C
    this->field_0x50 = 0;            // +0x50
    this->field_0x70 = 0;            // +0x70 (index 0x1c)
    this->field_0x74 = 0;            // +0x74
    this->field_0x78 = 0;            // +0x78
    this->field_0x7C = 0;            // +0x7C
    this->field_0x80 = 0;            // +0x80 (index 0x20)
    this->field_0x84 = 0;            // +0x84
    this->field_0x88 = 0;            // +0x88
    this->field_0x8C = 0;            // +0x8C
    this->field_0x90 = 0;            // +0x90
    this->field_0x94 = 0;            // +0x94
    this->field_0x98 = 0;            // +0x98
    this->field_0x9C = 0;            // +0x9C
    this->m_pfnSerialize = FUN_005fe070; // +0xA0 (index 0x28) – serialization function pointer
    this->field_0xA4 = 0;            // +0xA4
    this->m_pfnDestroy = FUN_005fda60;  // +0xA8 (index 0x2A) – cleanup function pointer
    this->field_0xAC = 0;            // +0xAC
    this->field_0xB0 = 0;            // +0xB0
    this->field_0xB4 = 0;            // +0xB4
    this->field_0xB8 = 0;            // +0xB8
    this->field_0xBC = 0;            // +0xBC
    this->field_0xC0 = 0;            // +0xC0
    this->field_0xC4 = 0;            // +0xC4
    this->field_0xE0 = 0;            // +0xE0 (index 0x38)
    this->field_0xE4 = 0;            // +0xE4
    this->field_0xE8 = 0;            // +0xE8
    this->field_0xEC = 0;            // +0xEC
    this->field_0xF0 = 0;            // +0xF0
    this->field_0xF4 = 0;            // +0xF4
    this->field_0xF8 = 0;            // +0xF8
    this->field_0xFC = 0;            // +0xFC
    this->field_0x100 = 0;           // +0x100
    this->field_0x104 = 0;           // +0x104
    this->field_0x108 = 0;           // +0x108
    this->field_0x10C = 0;           // +0x10C
    this->field_0x110 = 0;           // +0x110
    this->field_0x114 = 0x9000;      // +0x114 (index 0x45) – buffer size or capability flags
    this->field_0x118 = 0;           // +0x118
    this->field_0x11C = 0;           // +0x11C
    this->field_0x120 = 0;           // +0x120
    this->field_0x124 = 0;           // +0x124
    this->field_0xC = 0;             // +0x0C
    this->field_0x8 = 0;             // +0x08
    this->field_0x4 = 0;             // +0x04
    this->field_0x0 = 0;             // +0x00
    this->field_0x3C = 0;            // +0x3C
    this->field_0x38 = 0;            // +0x38
    this->field_0x34 = 0;            // +0x34
    this->field_0x30 = 0;            // +0x30
    this->field_0x6C = 0;            // +0x6C
    this->field_0x68 = 0;            // +0x68
    this->field_0x64 = 0;            // +0x64
    this->field_0x60 = 0;            // +0x60
    this->field_0xDC = 0;            // +0xDC
    this->field_0xD8 = 0;            // +0xD8
    this->field_0xD4 = 0;            // +0xD4
    this->field_0xD0 = 0;            // +0xD0
    this->field_0x2C = 0;            // +0x2C
    this->field_0x28 = 0;            // +0x28
    this->field_0x24 = 0;            // +0x24
    this->field_0x20 = 0;            // +0x20
    this->m_byteFlag40 = 0;          // +0x40 (byte at index 0x10, zeroed as byte)
    // Delete any existing sub‑object if it was previously allocated
    if (this->m_pSubObject != 0) {
        FUN_004daf90(this->m_pSubObject); // calls operator delete or cleanup
        this->m_pSubObject = 0;
    }
    // Last batch of zeros – these appear after the conditional but before return
    this->field_0x1C = 0;            // +0x1C
    this->field_0x18 = 0;            // +0x18
    this->field_0x14 = 0;            // +0x14
    this->field_0x10 = 0;            // +0x10
    this->field_0x13C = 0;           // +0x13C (index 0x4F)
    this->field_0x138 = 0;           // +0x138
    this->field_0x134 = 0;           // +0x134
    this->field_0x130 = 0;           // +0x130
    return this;
}