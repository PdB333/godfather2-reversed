// FUNC_NAME: MemoryPool::allocateAndInit
void __thiscall MemoryPool::allocateAndInit(void* this)
{
    undefined4* ptrToAllocData; // puVar1
    undefined4 fallbackBuffer[3]; // local_4 to local_c, 12 bytes

    // Retrieve allocation source from this+8
    ptrToAllocData = *(undefined4**)((char*)this + 8);
    if (ptrToAllocData == nullptr) {
        // Use local fallback if no allocation source
        fallbackBuffer[0] = 0;
        fallbackBuffer[1] = 0;
        fallbackBuffer[2] = 0;
        ptrToAllocData = fallbackBuffer;
    }

    // Call virtual allocation function at this+4 with size 0x18 and the allocation source
    ptrToAllocData = (undefined4*)((**(void(__thiscall**)(void*, uint32_t, undefined4*))(*((uint32_t*)this + 1)))(this, 0x18, ptrToAllocData);

    if (ptrToAllocData != nullptr) {
        // Zero first three dwords (offsets 0x00, 0x04, 0x08)
        ptrToAllocData[0] = 0;
    }
    if (ptrToAllocData + 1 != nullptr) {
        ptrToAllocData[1] = 0;
    }
    if (ptrToAllocData + 2 != nullptr) {
        ptrToAllocData[2] = 0;
    }

    // Set flags at offsets 0x15 and 0x14
    *(uint8_t*)((uint32_t)ptrToAllocData + 0x15) = 0;
    *(uint8_t*)(ptrToAllocData + 5) = 1; // offset 0x14 = byte at dword index 5
    return;
}