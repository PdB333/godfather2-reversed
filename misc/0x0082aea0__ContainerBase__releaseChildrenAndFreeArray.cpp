// FUNC_NAME: ContainerBase::releaseChildrenAndFreeArray
void __fastcall ContainerBase::releaseChildrenAndFreeArray(ContainerBase* this)
{
    uint count = this->count; // +0x0C (param_1[3])
    void** array = this->array; // +0x08 (param_1[2])
    
    // Set vtable pointer (constructor-like, but this is a destructor helper)
    this->vtable = &PTR_FUN_00d737f8; // +0x00
    
    // Release each child object by calling its first virtual function with flag 1
    for (uint i = 0; i < count; i++)
    {
        void* child = array[i];
        if (child != nullptr)
        {
            // Call virtual function at offset 0 (likely a release/destructor method)
            (*(void (__thiscall**)(void*, int))child)(child, 1);
        }
    }
    
    // Free the array itself
    if (array != nullptr)
    {
        operatorDeleteArray(array); // FUN_009c8f10
    }
}