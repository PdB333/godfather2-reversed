// FUNC_NAME: EARS::Framework::Entity::releaseInternalPointer

void __thiscall EARS::Framework::Entity::releaseInternalPointer(int this)
// Address: 0x006a8c80
// Role: Releases a resource pointed to by offset +0x40, then clears both +0x40 and +0x44.
// This is commonly used to free a dynamically allocated sub‑object and reset the storage.
{
    // dereference the pointer at +0x40 (this->m_pInternalResource)
    int *resourcePtr = *(int **)(this + 0x40);
    if (resourcePtr != 0)
    {
        // call the resource's destructor / deallocation function (FUN_005e3c00)
        FUN_005e3c00((int)resourcePtr);
        // clear both the pointer and the adjacent field (likely size or count)
        *(int *)(this + 0x40) = 0;
        *(int *)(this + 0x44) = 0;
    }
}