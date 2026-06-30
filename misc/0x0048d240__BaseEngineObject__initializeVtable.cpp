// FUNC_NAME: BaseEngineObject::initializeVtable
void __fastcall BaseEngineObject::initializeVtable(undefined4 ecxUnused, int* objectHandlePtr, int param3, int param4, int param5, int param6, int param7) {
    // Dereference handle to get the actual object pointer
    int objectBase = *objectHandlePtr;

    // Set the vtable pointer at offset 0x14 (custom virtual table arrangement)
    *(void**)(objectBase + 0x14) = &PTR_FUN_01123e2c;  // PTR_FUN_01123e2c is the vtable array

    // Advance the vtable pointer by 4 (likely to point to next base class vtable)
    int* vtablePtr = (int*)(objectBase + 0x14);
    *vtablePtr = *vtablePtr + 4;

    // Copy a block of 16 integers from the function's stack frame into a local array
    // This may be a compiler artifact; the array is not used further in this function
    typedef int StackCopy[16];
    StackCopy& localCopy = *(StackCopy*)((char*)&param3 - 0x18); // reconstructed based on stack offsets
    for (int i = 0; i < 16; i++) {
        localCopy[i] = ((int*)(&param3))[i]; // copy from stack arguments
    }

    // Call a secondary initialization routine with the last two parameters
    FUN_0048e6e0(param6, param7);
}