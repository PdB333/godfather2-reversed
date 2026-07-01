// FUNC_NAME: UnknownClass::`scalar deleting destructor' (0x00894880)
void* __thiscall UnknownClass::scalarDeletingDestructor(void* thisPtr, byte deletingFlag) {
    // Call the base/actual destructor (likely ~UnknownClass)
    FUN_00893d60(thisPtr);  // Base destructor call
    // If the deleting flag's least significant bit is set, free memory via operator delete
    if (deletingFlag & 1) {
        FUN_009c8eb0(thisPtr);  // operator delete
    }
    return thisPtr;
}