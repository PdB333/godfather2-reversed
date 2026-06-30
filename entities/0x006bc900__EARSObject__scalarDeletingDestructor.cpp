// FUNC_NAME: EARSObject::scalarDeletingDestructor
int* EARSObject::scalarDeletingDestructor(int* thisPtr, byte deletingFlag)
{
    // Check if object is valid (first word non-zero, usually vtable pointer)
    if (*thisPtr != 0) {
        // Call the actual destructor at address 0x004daf90
        FUN_004daf90(thisPtr);
    }
    // If the deleting flag's bit 0 is set, call operator delete at 0x009c8eb0
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(thisPtr);
    }
    return thisPtr;
}