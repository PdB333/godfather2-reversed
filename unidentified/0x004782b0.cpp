// FUN_NAME: UIColorManager::initColorTable
void __thiscall UIColorManager::initColorTable(void) // 0x004782b0
{
    // Global color constants (likely ARGB values)
    uint32_t color1 = DAT_00e2b050;          // default primary color
    uint32_t color2 = DAT_00e44614;          // default secondary color

    this->slotCount = 1;                     // +0x00: set to 1 indicating one active slot?

    // Loop initializes 4 color entries (each 16 bytes, interleaved storage)
    // Layout: [4 bytes flag][4x4 uint32_t colors0][4x4 uint32_t colors1][4x4 uint32_t colors2][4x4 uint8_t alpha/bytes]
    // Each iteration writes to all four interleaved arrays at offset i*4
    for (int i = 0; i < 4; i++)
    {
        uint32_t* base;                      // base pointer for this row
        base = &this->colors0[i];            // +0x04 + i*4
        *(base - 4) = color1;                // write to colors0[-1]?? Actually mapping from decompiler:
        // puVar3 = &this->colors0[0] + 5? This is confusing, but based on offsets:
        // Iteration i writes:
        //   +0x04 + i*4 = color1
        //   +0x14 + i*4 = color2
        //   +0x24 + i*4 = 0
        //   +0x34 + i*4 = bytes: 0x80,0x80,0x80,0xff
        *(uint32_t*)((uint8_t*)this + 0x04 + i*4) = color1;
        *(uint32_t*)((uint8_t*)this + 0x14 + i*4) = color2;
        *(uint32_t*)((uint8_t*)this + 0x24 + i*4) = 0;
        ((uint8_t*)this)[0x34 + i*4] = 0x80; // R
        ((uint8_t*)this)[0x34 + i*4 + 1] = 0x80; // G
        ((uint8_t*)this)[0x34 + i*4 + 2] = 0x80; // B
        ((uint8_t*)this)[0x34 + i*4 + 3] = 0xFF; // A
    }

    // Fifth entry: explicit initialization
    ((uint8_t*)this)[0x44] = 0;              // +0x44: R = 0
    ((uint8_t*)this)[0x45] = 0;              // +0x45: G = 0
    ((uint8_t*)this)[0x46] = 0;              // +0x46: B = 0
    ((uint8_t*)this)[0x47] = 0xFF;           // +0x47: A = 255

    *(uint32_t*)((uint8_t*)this + 0x48) = color1; // +0x48: color1
    *(uint32_t*)((uint8_t*)this + 0x4C) = color2; // +0x4C: color2
    *(uint32_t*)((uint8_t*)this + 0x50) = 0;      // +0x50: zero
}