// FUNC_NAME: SimManager::resolveObjectIndex
uint32_t __thiscall SimManager::resolveObjectIndex(int this, int index) {
    int adjustedIndex;
    uint32_t* ptr;

    // Retrieve the offset table at this+0x4
    int* offsetTable = *(int**)(this + 4);
    int base = offsetTable[1]; // Base offset for positive indices

    adjustedIndex = index - base;

    if (adjustedIndex < 0) {
        // Negative index: use the primary table directly (index * 0x70 + 0x40 base)
        ptr = (uint32_t*)(offsetTable[0] + 0x40 + index * 0x70);
        return *(uint32_t*)(*ptr + 0x10); // Return field at +0x10 of the pointed structure
    }

    // Positive index: check for a secondary manager at this+0x1c
    if (*(int*)(this + 0x1c) != 0) {
        int secondary = *(int*)(this + 0x1c);
        // Dereference chain: secondary->[0x10]->[0x30]->[0] gives a base pointer
        int* p = *(int**)(*(int*)(secondary + 0x10) + 0x30);
        ptr = (uint32_t*)((uint32_t)p + 0x40 + adjustedIndex * 0x70);
        return *(uint32_t*)(*ptr + 0x14); // Return field at +0x14 of the pointed structure
    } else {
        // Fallback: use a global pointer at address 0x30 (likely g_simObjectBase)
        int globalBase = *(int*)(0x30);
        ptr = (uint32_t*)(globalBase + 0x40 + adjustedIndex * 0x70);
        return *(uint32_t*)(*ptr + 0x14);
    }
}