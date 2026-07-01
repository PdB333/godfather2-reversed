// FUNC_NAME: scalar_deleting_destructor
// Address: 0x0084c3c0
// Role: Scalar deleting destructor — calls object destructor and optionally frees memory (flags bit 0 controls deletion)

// Forward declarations for called functions
void __thiscall objectDestructor(int* thisPointer); // 0x004daf90
void __cdecl operatorDelete(void* pointer);         // 0x009c8eb0

int* __thiscall scalarDeletingDestructor(int* thisPointer, byte flags) {
    // If the object's first field (e.g., vtable pointer or allocated memory) is non-null,
    // invoke the actual destructor to release resources.
    if (thisPointer[0] != 0) {
        objectDestructor(thisPointer);
    }

    // If the low bit of flags is set, deallocate the memory block.
    if ((flags & 1) != 0) {
        operatorDelete(thisPointer);
    }

    // Return the original pointer, as is typical for this pattern.
    return thisPointer;
}