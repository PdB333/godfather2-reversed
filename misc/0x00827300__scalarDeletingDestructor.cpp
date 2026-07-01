// FUNC_NAME: scalarDeletingDestructor
// Address: 0x00827300
// Role: MSVC scalar deleting destructor - calls class destructor (0x004daf90) and optionally operator delete (0x009c8eb0) based on deleteFlag.
int* __thiscall scalarDeletingDestructor(int* thisPointer, byte deleteFlag)
{
    // If the object's vtable pointer (or similar) is non-zero, call the destructor.
    if (*thisPointer != 0) {
        FUN_004daf90(thisPointer); // Destructor at 0x004daf90
    }
    // If the low bit of deleteFlag is set, call operator delete to free the memory.
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(thisPointer); // operator delete at 0x009c8eb0
    }
    return thisPointer;
}