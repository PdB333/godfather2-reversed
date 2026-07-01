// FUNC_NAME: GameObjectBase::~GameObjectBase
void* __thiscall GameObjectBase::~GameObjectBase(byte deleteFlag) {
    // Set vtable to destructor stage 1
    this->vtable = &PTR_FUN_00d7343c;
    
    // Free pointer at offset 0x5C if non-null
    if (this->field_0x5C != 0) {
        releaseSomePointer(this + 0x5C); // FUN_004daf90
    }
    
    // Set vtable to destructor stage 2 (prevent virtual calls during base destruction)
    this->vtable = &PTR_LAB_00e32854;
    
    // If delete flag is set, deallocate memory via custom allocator
    if ((deleteFlag & 1) != 0) {
        int* allocatorTable = (int*)getAllocatorTable(); // FUN_009c8f80
        // Call operator delete (size 0x70) from allocator vtable at offset 4
        (**(code**)(*allocatorTable + 4))(this, 0x70);
    }
    
    return this;
}