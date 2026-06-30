// FUNC_NAME: SomeManager::updateDirtyItems
void SomeManager::updateDirtyItems(int *thisPtr)
{
    if (thisPtr == nullptr)
        return;
    
    // Virtual call at vtable+0x5c: perhaps isActive() or hasPendingChanges()
    if (!(**(code **)(*thisPtr + 0x5c))())
        return;
    
    // Virtual call at vtable+0x08: get a reference object for comparison
    int *refObj = (int *)(**(code **)(*thisPtr + 8))();
    
    // Virtual call at vtable+0x20: get count of items to iterate
    uint count = (**(code **)(*thisPtr + 0x20))();
    if (count == 0)
        return;
    
    uint index = 0;
    do {
        // Virtual call at vtable+0x24: get item at index
        int *item = (int *)(**(code **)(*thisPtr + 0x24))(index);
        
        // Virtual call on item at vtable+0x0c: get some ID (e.g., network ID, type ID)
        int itemId = (**(code **)(*item + 0xc))();
        int refId = (**(code **)(*refObj + 0xc))();
        
        if (itemId != refId) {
            int idCopy = itemId;
            // Call some helper that checks if this ID is already tracked
            // Possibly sets a local flag (iStack_10) to indicate if found
            FUN_0065dda0(&idCopy);
            int foundFlag = iStack_10; // local variable, set by FUN_0065dda0? or from earlier?
            if (foundFlag == 0) {
                // ID not found, so add it
                idCopy = itemId;
                // Convert ID to some other representation (e.g., string or hash)
                FUN_0065de00(auStack_4, &idCopy);
                idCopy = itemId;
                FUN_0065dda0(&idCopy);
                
                // Allocate a new object of size 0x10 (16 bytes)
                int *newObj = (int *)FUN_009c8e50(0x10);
                if (newObj != nullptr) {
                    // Initialize the object (likely constructor)
                    int initVal = FUN_0065dc50();
                    // Store the object at some offset (iStack_c + 4) - iStack_c might be a pointer from the class
                    *(int *)(iStack_c + 4) = initVal;
                }
            }
        }
        index++;
    } while (index < count);
}