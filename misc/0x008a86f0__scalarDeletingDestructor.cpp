// FUNC_NAME: scalarDeletingDestructor
int* __thiscall scalarDeletingDestructor(int* thisPtr, byte flag) {
    // If the object pointer is non-null, call the actual destructor (FUN_004daf90)
    if (*thisPtr != 0) {
        FUN_004daf90(thisPtr);
    }
    // If the low bit of flag is set, free the memory via operator delete (FUN_009c8eb0)
    if ((flag & 1) != 0) {
        FUN_009c8eb0(thisPtr);
    }
    return thisPtr;
}