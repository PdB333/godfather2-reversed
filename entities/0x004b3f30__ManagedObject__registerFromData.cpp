// FUNC_NAME: ManagedObject::registerFromData
void __thiscall ManagedObject::registerFromData(uint32_t* pData) {
    // Global allocation pointer: base + 0x14 holds current position in a memory pool
    int* pAllocPos = reinterpret_cast<int*>(DAT_01206880 + 0x14);

    // Copy 0x5c bytes (23 dwords) from input data to object's internal buffer at +0x44
    uint32_t* src = pData;
    uint32_t* dst = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x44);
    for (int i = 0x17; i != 0; --i) {
        *dst++ = *src++;
    }

    // Modify flags at offset 0x18: clear bits 4 and 6, set bit 5
    // This likely marks the object as "initialized" or "active" in a specific state
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x18) =
        (*reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x18) & 0xffffffaf) | 0x20;

    // Work with global allocation: each registration writes a vtable pointer, an object pointer,
    // then allocates separate space for the data copy.
    int* currentSlot = reinterpret_cast<int*>(*pAllocPos);

    // Copy input data to a temporary stack buffer (local_c0)
    uint32_t tempCopy[23];
    src = pData;
    for (int i = 0x17; i != 0; --i) {
        tempCopy[i-1] = *src++; // Note: loop decrements i, so i starts at 0x17, assigns to tempCopy[i-1]? Actually original code does *puVar4 = *param_2 with puVar4 incrementing, so it's sequential. We'll fix.
    }
    // Actually original stores sequentially: let's rewrite correctly.
    // Reset src:
    src = pData;
    for (int i = 0; i < 23; ++i) {
        tempCopy[i] = src[i];
    }

    // Write vtable pointer into the global allocation slot
    *currentSlot = reinterpret_cast<int>(&PTR_FUN_01124578); // address of some vtable or function table
    *pAllocPos += 4; // move past this slot
    currentSlot = reinterpret_cast<int*>(*pAllocPos);

    // Write this pointer (the object) into the next slot
    *currentSlot = reinterpret_cast<int>(this);
    *pAllocPos += 4;

    // Compute aligned destination for the data copy: ensure 4-byte alignment with an offset of at least 7? (unusual alignment)
    void* alignedDst = reinterpret_cast<void*>((*pAllocPos + 7U) & 0xfffffffc);
    *pAllocPos = reinterpret_cast<int>(alignedDst);

    // Copy the data (0x5c bytes) from the temporary copy to the aligned location
    __memcpy(alignedDst, tempCopy, 0x5c);

    // Advance allocation pointer past the copied data
    *pAllocPos += 0x5c;
}