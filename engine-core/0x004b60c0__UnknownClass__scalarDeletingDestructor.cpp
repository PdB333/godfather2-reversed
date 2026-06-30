// FUNC_NAME: UnknownClass::scalarDeletingDestructor
void* __thiscall UnknownClass::scalarDeletingDestructor(void* this, byte deleteFlag) {
    // Call the actual destructor (FUN_004b6250)
    this->destructor();

    // If deletion is requested, deallocate memory
    if (deleteFlag & 1) {
        // Get the global delete dispatcher object (FUN_009c8f80)
        // The dispatcher's first member is a pointer to a vtable of delete functions
        int* dispatcherPtr = (int*)getDeleteDispatcher();
        int* deleteVtable = (int*)*dispatcherPtr; // dereference to get vtable pointer
        // The delete function is at vtable offset 4 (second entry)
        // It is a __thiscall taking the object pointer and size (0x2c = 44 bytes)
        typedef void (__thiscall *DeleteFunc)(void* obj, int size);
        DeleteFunc delFunc = (DeleteFunc)deleteVtable[1]; // equivalent to *(deleteVtable + 1)
        delFunc(this, 0x2c);
    }

    return this;
}