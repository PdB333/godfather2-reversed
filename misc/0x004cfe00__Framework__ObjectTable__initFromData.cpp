// FUNC_NAME: Framework::ObjectTable::initFromData
void __thiscall Framework::ObjectTable::initFromData(void *this, uint32_t param_1, uint32_t param_2) {
    uint32_t baseOffset = *(uint32_t *)((uint8_t *)this + 0x40); // +0x40: base offset for relocation
    uint8_t *entryPtr = (uint8_t *)(*(uint32_t *)((uint8_t *)this + 0xC) + (uint32_t)this); // +0xC: relative offset to entry array, converted to absolute

    // Set up pointer to secondary table or offset
    if (*(uint16_t *)((uint8_t *)this + 0x448) == 0) {
        *(uint32_t *)((uint8_t *)this + 0x450) = 0; // +0x450: secondary table pointer/offset
    } else {
        *(uint32_t *)((uint8_t *)this + 0x450) = *(uint32_t *)((uint8_t *)this + 0x44C) + (uint32_t)this; // +0x44C: relative offset, stored as absolute
    }

    // Relocate 256-pointer table at +0x44
    uint32_t *tableEntry = (uint32_t *)((uint8_t *)this + 0x44);
    for (int i = 0; i < 256; i++) {
        if (*tableEntry != 0) {
            *tableEntry = (uint32_t)this + *tableEntry + baseOffset;
        }
        tableEntry++;
    }

    // Process entries (each 24 bytes) to link objects
    uint16_t entryCount = *(uint16_t *)((uint8_t *)this + 0xA); // +0xA: number of entries
    if (entryCount != 0) {
        for (uint16_t j = 0; j < entryCount; j++) {
            uint8_t *entry = entryPtr + (j * 24);
            uint8_t entryByte0 = entry[0]; // index inside target object's table
            uint8_t entryByte1 = entry[1]; // index into the 256-pointer table

            uint32_t *targetTable = (uint32_t *)((uint8_t *)this + 0x44);
            uint32_t targetPtr = targetTable[entryByte1];

            if (targetPtr != 0) {
                // Store pointer to this entry in the target object's table at offset entryByte0*4
                *(uint32_t *)(targetPtr + (uint32_t)entryByte0 * 4) = (uint32_t)entry;
            }
        }
    }

    *(uint32_t *)((uint8_t *)this + 0x444) = param_2; // +0x444: store second parameter
    *(uint32_t *)((uint8_t *)this + 0x0) = param_1;   // +0x0: store first parameter as vtable or data pointer
}