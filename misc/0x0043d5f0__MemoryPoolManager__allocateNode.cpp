// FUNC_NAME: MemoryPoolManager::allocateNode
int* __fastcall MemoryPoolManager::allocateNode(void* this, void* ediParam)
{
    int* allocatedBlock;
    GUID unusedGuid; // 12-byte stack buffer, zeroed
    unusedGuid.data1 = 0;
    unusedGuid.data2 = 0;
    unusedGuid.data3 = 0;

    // Virtual call: first vtable function is an allocator.
    // It takes (ediParam + 0xC) as the memory pool base and &unusedGuid as output GUID.
    // The returned pointer is a 12-byte (3 int) block from the pool.
    allocatedBlock = (int*)(this->vtable[0])((uint8_t*)ediParam + 0xC, &unusedGuid);

    if (allocatedBlock != nullptr)
    {
        // Initialize the allocated node structure (3 fields):
        // +0x00: pointer to the object represented by ediParam
        // +0x04: reserved (zero)
        // +0x08: global constant (likely a type ID or configuration)
        allocatedBlock[0] = (int)ediParam;
        allocatedBlock[1] = 0;
        allocatedBlock[2] = DAT_0110ab98; // global value
        return allocatedBlock;
    }

    return nullptr;
}