// FUNC_NAME: PoolManager::allocateWithSlotIndex
int PoolManager::allocateWithSlotIndex(int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8)
{
    // Allocate a new entry in the pool using the first 5 parameters and arg8
    int entryHandle = allocateNewEntry(arg2, arg3, arg4, arg5, arg8);
    
    // Try to assign a slot index using arg6
    int slotIndex = getSlotIndex(entryHandle, arg6);
    
    if (slotIndex == -1) {
        // Slot full or invalid – free the allocated entry and return failure
        deallocateEntry(entryHandle, 0);
        return 0xffffffff; // -1
    }
    
    return entryHandle;
}