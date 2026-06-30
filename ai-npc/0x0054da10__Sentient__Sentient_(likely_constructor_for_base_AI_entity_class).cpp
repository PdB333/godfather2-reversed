// FUNC_NAME: Sentient::Sentient (likely constructor for base AI entity class)
void* __fastcall Sentient::Sentient(Sentient* thisPtr) {
    int* embeddedPtr;
    int someGlobal1;
    int someGlobal2;
    int someGlobal3;

    someGlobal1 = DAT_00e44830;   // global constant
    someGlobal2 = DAT_00e2eff4;   // another global
    someGlobal3 = DAT_00e2cd58;   // global window/sequence constant
    someGlobal4 = DAT_00e2cd5c;   // global

    // Set vtable pointer (offset 0x00)
    thisPtr[0] = &PTR_FUN_00e39f10;

    // Offset 0x60: magic type identifier (0xfe16702f)
    thisPtr[0x18] = 0xfe16702f;

    // Offsets 0xC4, 0xC8: two pointer fields set to someGlobal2
    thisPtr[0x31] = someGlobal2;
    thisPtr[0x32] = someGlobal2;

    // Offset 0xBC: second vtable or interface pointer
    thisPtr[0x2f] = &PTR_LAB_00e39f14;
    thisPtr[0x30] = 0;

    // Offset 0xC0: set to someGlobal3
    thisPtr[0x36] = 0;
    thisPtr[0x37] = 0;
    thisPtr[0x39] = 0;
    thisPtr[4] = someGlobal3;   // offset 0x10

    // Zero out several blocks of floats/vectors
    thisPtr[5] = 0;  // offset 0x14
    thisPtr[6] = 0;  // offset 0x18
    thisPtr[7] = 0;  // offset 0x1C
    thisPtr[8] = 0;  // offset 0x20

    // Byte at offset 0x0C set to 0
    *(byte*)((uint)thisPtr + 0x0C) = 0;
    // Byte at offset 0x31 set to 0
    *(byte*)((int)thisPtr + 0x31) = 0;

    // Zero out blocks: 0x40-0x4C, 0x50-0x5C, 0x60-0x6C (3 entries), 0x70-0x7C, 0x80-0x88 (3 entries), 0x90-0x9C
    thisPtr[0x13] = 0; // offset 0x4C
    thisPtr[0x12] = 0; // 0x48
    thisPtr[0x11] = 0; // 0x44
    thisPtr[0x10] = 0; // 0x40

    thisPtr[0x17] = 0; // 0x5C
    thisPtr[0x16] = 0; // 0x58
    thisPtr[0x15] = 0; // 0x54
    thisPtr[0x14] = 0; // 0x50

    // 3-entry block at 0x60, 0x64, 0x68 (first was magic, rest zero)
    thisPtr[0x1b] = 0; // 0x6C
    thisPtr[0x1a] = 0; // 0x68
    thisPtr[0x19] = 0; // 0x64

    thisPtr[0x1f] = 0; // 0x7C
    thisPtr[0x1e] = 0; // 0x78
    thisPtr[0x1d] = 0; // 0x74
    thisPtr[0x1c] = 0; // 0x70

    // 3-entry block at 0x80, 0x84, 0x88
    thisPtr[0x22] = 0; // 0x88
    thisPtr[0x21] = 0; // 0x84
    thisPtr[0x20] = 0; // 0x80

    thisPtr[0x27] = 0; // 0x9C
    thisPtr[0x26] = 0; // 0x98
    thisPtr[0x25] = 0; // 0x94
    thisPtr[0x24] = 0; // 0x90

    // Set global constants at offsets 0xA0, 0xA8, 0xAC, etc.
    thisPtr[0x28] = someGlobal1;    // offset 0xA0
    thisPtr[0x2a] = DAT_00e2cd58;   // offset 0xA8
    thisPtr[0x29] = 0;              // offset 0xA4
    thisPtr[0x2b] = DAT_00e2cd5c;   // offset 0xAC
    thisPtr[0x2c] = 0;              // offset 0xB0
    thisPtr[0x2d] = 0;              // offset 0xB4
    thisPtr[0x2e] = 1;              // offset 0xB8 (initial flag)

    thisPtr[0x33] = 0; // offset 0xCC
    thisPtr[0x34] = 0; // offset 0xD0
    thisPtr[0x35] = 0; // offset 0xD4

    // Check embedded pointer at offset 0xD8
    embeddedPtr = (int*)&thisPtr[0x36];
    if (*embeddedPtr != 0) {
        // Likely destructor for embedded object
        FUN_004daf90(embeddedPtr);
        *embeddedPtr = 0;
    }

    // Final fields: offset 0xE0, 0xE4, 0xE8
    thisPtr[0x39] = 0;   // offset 0xE4
    thisPtr[0x3a] = 2;   // offset 0xE8
    thisPtr[0x38] = 8;   // offset 0xE0
    // Set bit 1 (0x2) in field at 0xE4
    thisPtr[0x39] = thisPtr[0x39] | 2;
    // Clear bit 3 (0x8) in same field
    thisPtr[0x39] = thisPtr[0x39] & 0xFFFFFFF7;

    // Reset these two to initial values
    thisPtr[0x2d] = 0;
    thisPtr[0x2e] = 1;

    return thisPtr;
}