// FUNC_NAME: scalarDeletingDestructor (likely for class with destructor at 0x0073b910)
// This is a scalar deleting destructor pattern: calls the actual destructor (FUN_0073b910) and if the flag's LSB is set, also calls operator delete (FUN_00624da0) to free the memory.
void* __thiscall scalarDeletingDestructor(void* thisptr, byte flags) {
    // Call the actual destructor (likely virtual or non-virtual)
    destructor(thisptr);

    // Check if the scalar delete flag (bit 0) is set
    if ((flags & 0x1) != 0) {
        // Call operator delete to free the memory block
        operatorDelete(thisptr);
    }

    // Return the original pointer (standard scalar deleting destructor behavior)
    return thisptr;
}