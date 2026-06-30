// FUNC_NAME: ObjectManager::updateAllObjects
void ObjectManager::updateAllObjects(ObjectManager* thisPtr)
{
    uint index = 0;
    
    // Iterate through all active objects in the manager
    if (*(int*)(thisPtr + 0x1c) != 0) {
        undefined4** objectPtr = (undefined4**)(thisPtr + 8);
        do {
            // Call the update method (vtable offset 0x10) on each object
            (**(code**)(*(int*)*objectPtr + 0x10))();
            index = index + 1;
            objectPtr = objectPtr + 1;
        } while (index < *(uint*)(thisPtr + 0x1c));
    }
    
    // Call the manager's own update method (vtable offset 0xc)
    (**(code**)(**(int**)(thisPtr + 0x20) + 0xc))();
    
    // Call cleanup/finalize function
    FUN_005651e0(thisPtr);
    return;
}