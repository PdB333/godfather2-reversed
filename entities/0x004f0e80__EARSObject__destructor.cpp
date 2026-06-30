// FUNC_NAME: EARSObject::destructor

void __thiscall EARSObject::destructor(EARSObject* this)
{
    int* pListEnd;
    int iChildPtr;
    
    // Set vtable to base class (for virtual destructor chain)
    this->vtablePtr = &PTR_FUN_00e37440;
    
    // If the child object pointer exists, call a virtual method on it
    // childObj is at offset 0x28, this+0x30 is a field (e.g., data pointer)
    if (this->childObj != nullptr) {
        // Call virtual method at vtable+4: probably releaseChild
        (*(void(__thiscall**)(int, void*))(*(int*)this->childObj + 4))(this->someOtherObj, &this->data);
        
        // If the flag at offset 0x2C is set, insert this into a global delete list
        if (this->flagDestroyOnRelease != '\0') {
            // Get pointer to end of pending deletion list (global +0x14)
            pListEnd = (int*)(*(int*)(g_memoryManager + 0x14));
            // Write sentinel and push this pointer onto the list
            **(int**)(g_memoryManager + 0x14) = (int)&PTR_LAB_01124d50;
            *pListEnd = *pListEnd + 4;
            **(int**)(*pListEnd) = (int)this;
            *pListEnd = *pListEnd + 4;
        }
    }
    
    // Set vtable to derived class vtable (likely this class's own vtable)
    this->vtablePtr = &PTR_FUN_00e37110;
    
    // If there is a pending destroy ID (offset 0x10), insert it into another global list
    iChildPtr = this->pendingDestroyId;  // offset 0x10
    if (iChildPtr != 0) {
        pListEnd = (int*)(*(int*)(g_memoryManager + 0x14));
        **(int**)(g_memoryManager + 0x14) = (int)&PTR_LAB_01123be8;
        *pListEnd = *pListEnd + 4;
        *(int*)(*pListEnd) = iChildPtr;
        *pListEnd = *pListEnd + 4;
        
        // Clear the ID and next pointer at offsets 0x10 and 0x14
        this->pendingDestroyId = 0;
        this->nextPendingDestroy = 0;
    }
    return;
}