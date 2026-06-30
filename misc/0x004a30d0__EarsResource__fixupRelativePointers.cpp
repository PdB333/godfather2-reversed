// FUNC_NAME: EarsResource::fixupRelativePointers
int* __thiscall EarsResource::fixupRelativePointers(uint32_t size)
{
    // Check validity: non-null this, size > 103, magic "ldMM" at +0x00, version 14 at +0x04
    if (this == nullptr || size <= 0x67 || header.magic != 0x4d4d646c || header.version != 0xe)
        return nullptr;

    // Relocate top-level pointer arrays (offsets are relative to this)
    // Arrays are stored as relative offsets, need to be converted to absolute pointers
    for (int i = 0; i < 9; ++i) {
        int* ptrField = &header.arrays[i];
        if (*ptrField != 0)
            *ptrField = reinterpret_cast<int*>((uint8_t*)this + *ptrField);
    }

    // Section 1: Sub-object array at this->arrays[0] (offset +0x38), count at +0x5a
    uint16_t count1 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x5a);
    for (uint16_t i = 0; i < count1; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[0] + i * 0x30; // 48 bytes per element
        // Fixup pointers within each sub-object
        if (*(int*)(elem + 8) != 0)  // +0x08: pointer
            *(int*)(elem + 8) += (int)this;
        if (*(int*)(elem + 4) != 0)  // +0x04: pointer
            *(int*)(elem + 4) += (int)this;
        if (*(int*)(elem + 0x24) != 0) // +0x24: pointer to array of pointers
            *(int*)(elem + 0x24) += (int)this;
        if (*(int*)(elem + 0x28) != 0) // +0x28: pointer to array of pointers
            *(int*)(elem + 0x28) += (int)this;
        if (*(int*)(elem + 0x1c) != 0) // +0x1c: pointer to array of pointers
            *(int*)(elem + 0x1c) += (int)this;

        // Fixup the array at +0x24 (count at +0x2c)
        uint16_t count24 = *(uint16_t*)(elem + 0x2c);
        for (uint16_t j = 0; j < count24; ++j) {
            int* arr = *(int**)(elem + 0x24);
            if (arr[j] != 0)
                arr[j] += (int)this;
        }

        // Fixup the array at +0x1c (count at +0x20)
        uint16_t count1c = *(uint16_t*)(elem + 0x20);
        for (uint16_t j = 0; j < count1c; ++j) {
            int* arr = *(int**)(elem + 0x1c);
            if (arr[j] != 0)
                arr[j] += (int)this;
        }

        // Fixup the array at +0x28 (count at +0x2e)
        uint16_t count28 = *(uint16_t*)(elem + 0x2e);
        for (uint16_t j = 0; j < count28; ++j) {
            int* arr = *(int**)(elem + 0x28);
            if (arr[j] != 0)
                arr[j] += (int)this;
        }
    }

    // Section 2: Array at this->arrays[1] (offset +0x3c), count at +0x5c, element size 0xc
    uint16_t count2 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x5c);
    for (uint16_t i = 0; i < count2; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[1] + i * 0x0c;
        if (*(int*)(elem + 0) != 0) // single pointer at +0x00
            *(int*)(elem + 0) += (int)this;
    }

    // Section 3: Array at this->arrays[2] (offset +0x40), count at +0x5e, element size 0x18
    uint16_t count3 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x5e);
    for (uint16_t i = 0; i < count3; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[2] + i * 0x18;
        int* ptrField1 = (int*)(elem + 0); // first int (flags/type)
        int* ptrField4 = (int*)(elem + 4);
        int* ptrField8 = (int*)(elem + 8);
        int* ptrField14 = (int*)(elem + 0x14); // flags mask

        if (*ptrField4 != 0)
            *ptrField4 += (int)this;
        if (*ptrField8 != 0)
            *ptrField8 += (int)this;
        // Only fixup first field if certain flags set (mask 0x3b8)
        if ((*ptrField14 & 0x3b8) != 0 && *ptrField1 != 0)
            *ptrField1 += (int)this;
    }

    // Section 4: Array at this->arrays[3] (offset +0x44), count at +0x60, element size 0xc
    uint16_t count4 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x60);
    for (uint16_t i = 0; i < count4; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[3] + i * 0x0c;
        // Pointer at +0x04 within the element
        if (*(int*)(elem + 4) != 0)
            *(int*)(elem + 4) += (int)this;
    }

    // Section 5: Array at this->arrays[4] (offset +0x48), count at +0x62, element size 0x24
    uint16_t count5 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x62);
    for (uint16_t i = 0; i < count5; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[4] + i * 0x24;
        if (*(int*)(elem + 8) != 0)  // +0x08
            *(int*)(elem + 8) += (int)this;
        if (*(int*)(elem + 4) != 0)  // +0x04
            *(int*)(elem + 4) += (int)this;
        if (*(int*)(elem + 0x1c) != 0) // +0x1c: pointer to array of pointers
            *(int*)(elem + 0x1c) += (int)this;

        // Fixup array at +0x1c (count at +0x20)
        uint16_t count1c = *(uint16_t*)(elem + 0x20);
        for (uint16_t j = 0; j < count1c; ++j) {
            int* arr = *(int**)(elem + 0x1c);
            if (arr[j] != 0)
                arr[j] += (int)this;
        }
    }

    // Section 6: Array at this->arrays[5] (offset +0x4c), count at +0x64, element size 0x24
    uint16_t count6 = *reinterpret_cast<uint16_t*>((uint8_t*)this + 0x64);
    for (uint16_t i = 0; i < count6; ++i) {
        uint8_t* elem = (uint8_t*)header.arrays[5] + i * 0x24;
        if (*(int*)(elem + 8) != 0)
            *(int*)(elem + 8) += (int)this;
        if (*(int*)(elem + 4) != 0)
            *(int*)(elem + 4) += (int)this;
        if (*(int*)(elem + 0x1c) != 0)
            *(int*)(elem + 0x1c) += (int)this;

        uint16_t count1c = *(uint16_t*)(elem + 0x20);
        for (uint16_t j = 0; j < count1c; ++j) {
            int* arr = *(int**)(elem + 0x1c);
            if (arr[j] != 0)
                arr[j] += (int)this;
        }
    }

    return this;
}