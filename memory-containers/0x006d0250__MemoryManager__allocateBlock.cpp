// FUNC_NAME: MemoryManager::allocateBlock
void __cdecl allocateBlock(void* param_1)
{
    // Returned pointer from static getter (likely a global memory manager singleton)
    MemoryManager* memoryManager = reinterpret_cast<MemoryManager*>(FUN_009c8f80());

    // Parameter block for allocation: pool ID=2, size=0x10, flags=0
    AllocationParams allocParams;
    allocParams.pool = 2;
    allocParams.size = 0x10;
    allocParams.flags = 0;

    // Call first virtual function of MemoryManager (virtual destructor + allocation?) 
    // calling convention: (this, &allocParams)
    memoryManager->vtable->allocate(memoryManager, &allocParams);
}