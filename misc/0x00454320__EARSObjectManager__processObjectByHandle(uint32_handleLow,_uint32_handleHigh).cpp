// FUNC_NAME: EARSObjectManager::processObjectByHandle(uint32 handleLow, uint32 handleHigh)
void __thiscall EARSObjectManager::processObjectByHandle(uint32 handleLow, uint32 handleHigh) {
    // Look up the object using the handles and this (likely the object factory)
    // FUN_004544a0 returns a pointer to the object or nullptr
    int *objectPtr = (int *)findObjectByHandle(handleLow, handleHigh, this);
    
    // If an object was found, invoke its virtual method at vtable offset +0x40
    if (objectPtr != (int *)0x0) {
        (*(code **)(*objectPtr + 0x40))();  // void __thiscall method()
    }
    return;
}