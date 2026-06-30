// FUNC_NAME: Allocator::allocateAndInitialize
void* __thiscall Allocator::allocateAndInitialize(void* sourceData)
{
    // +0x00: vtable pointer
    // +0x04: pre-allocated buffer (can be null)
    void* preAllocatedBuffer = *(void**)((char*)this + 4);
    void* hint;
    uint fallbackBuffer[3]; // used when preAllocatedBuffer is null
    if (preAllocatedBuffer == nullptr) {
        hint = &fallbackBuffer;
    } else {
        hint = preAllocatedBuffer;
    }

    // Virtual call to the allocator's allocation method (vtable[0])
    // Signature: void* allocate(uint size, void* hint)
    void* allocatedMem = (*(void* (**)(uint, void*))**(void***)this)(0xc, hint);
    if (allocatedMem != nullptr) {
        // First field: from uninitialized local (garbage/zero)
        *(uint*)allocatedMem = fallbackBuffer[2];
        // Second field: captures the return address of this function (caller's address)
        *((uint*)allocatedMem + 1) = (uint)__builtin_return_address(0); // return address
        // Third field: from the source data pointer
        *((uint*)allocatedMem + 2) = *(uint*)sourceData;
    }
    return allocatedMem;
}