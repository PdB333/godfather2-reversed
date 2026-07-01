// FUNC_NAME: MemoryManager::allocateAndConstruct
undefined4 __thiscall MemoryManager::allocateAndConstruct(void)
{
    MemoryManager *pManager;
    int allocationResult;
    undefined4 constructedObject;
    AllocationParams params;
    
    pManager = MemoryManager::getInstance(); // returns singleton at 0x009c8f80
    // Allocation parameters: pool=2, alignment=0x10, flags=0
    params.pool = 2;
    params.alignment = 0x10;
    params.flags = 0;
    
    // Virtual call to allocate memory (0xa0 = 160 bytes)
    allocationResult = (*(pManager->vtable))(pManager, 0xa0, &params);
    if (allocationResult != 0) {
        constructedObject = FUN_00831610(); // object constructor
        return constructedObject;
    }
    return 0;
}