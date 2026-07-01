// FUNC_NAME: SomeClass::destroyAndDeallocate
int* __thiscall SomeClass::destroyAndDeallocate(int* thisPtr, byte deallocFlag)
{
    // Check if the object is valid (vtable pointer or reference count at offset 0)
    if (*thisPtr != 0) {
        // Call the actual destructor
        FUN_004daf90(thisPtr);
    }
    // If the deallocation flag (bit 0) is set, free the memory
    if ((deallocFlag & 1) != 0) {
        // Call operator delete or custom deallocation
        FUN_009c8eb0(thisPtr);
    }
    return thisPtr;
}