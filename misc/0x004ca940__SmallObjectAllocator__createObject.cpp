// FUNC_NAME: SmallObjectAllocator::createObject
// Address: 0x004ca940
// Reconstructed from Ghidra decompile. This function is likely part of EA EARS memory management,
// allocating a small (0x18 bytes) object from a pool or using a virtual allocator, then copying
// data from a source object (passed in ESI) and storing an extra parameter.

void __thiscall SmallObjectAllocator::createObject(void* thisPtr, uint32_t extraParam)
{
    // +0x04: Pointer to a vtable (or function table) - first entry is an allocation function
    // +0x08: Optional memory hint (if non-null, used as hint; else a stack buffer is used)
    void* memoryHint = *(void**)((uint8_t*)thisPtr + 8);
    uint32_t stackBackup[3]; // local_c, local_8, local_4

    if (memoryHint == nullptr) {
        stackBackup[0] = 0;
        stackBackup[1] = 0;
        stackBackup[2] = 0;
        memoryHint = stackBackup;
    }

    // Call the allocator function from vtable with size 0x18 and the hint
    typedef void* (__thiscall *AllocFunc)(void* self, uint32_t size, void* hint);
    AllocFunc allocFunc = *(AllocFunc*)(*(void***)thisPtr + 0); // first virtual function
    void* newBlock = allocFunc(thisPtr, 0x18, memoryHint);

    if (newBlock != nullptr) {
        uint32_t* newMem = (uint32_t*)newBlock;
        uint32_t* source = (uint32_t*)__get_es_register(); // ESI holds source object pointer

        // Fill the allocated block
        newMem[0] = stackBackup[0];       // field +0x00 (copy of local stack values?)
        newMem[1] = (uint32_t)__get_eip_after_call(); // unaff_retaddr - possibly return address stored for debug?
        newMem[2] = extraParam;            // +0x08: extra parameter
        newMem[3] = source[0];             // +0x0C: copy of source object's first dword
        newMem[4] = source[1];             // +0x10: copy of source object's second dword
        *(uint8_t*)(newBlock + 0x14) = 0;  // +0x14 flags? (set to 0)
        *(uint8_t*)(newBlock + 0x15) = 0;  // +0x15 flags? (set to 0)
    }
}