// FUNC_NAME: SomeManager::getPointerByObjectIndex
int __thiscall SomeManager::getPointerByObjectIndex(void)
{
    int objectPtr; // stack variable to hold the resolved object pointer
    // Call to resolve an object handle into a pointer
    FUN_00573db0(&objectPtr);
    // objectPtr is now a pointer to some object
    // Check if valid and if the index in the object (at +0x14) is within bounds
    if ((objectPtr != 0) && 
        (*(int *)(objectPtr + 0x14) >= 0) && 
        (*(int *)(objectPtr + 0x14) < *(int *)(this + 0x20))) // this+0x20 = count
    {
        // return pointer to element at index: base + index * 8
        return *(int *)(this + 0x24) + (*(int *)(objectPtr + 0x14)) * 8; // this+0x24 = array base
    }
    return 0;
}