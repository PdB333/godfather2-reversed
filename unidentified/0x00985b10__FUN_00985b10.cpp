//FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x00985b10
// Role: Scalar deleting destructor (compiler-generated) for an unknown class.
// Calls the actual destructor (FUN_00985830) and, if the low bit of flags is set,
// calls a deallocation function (FUN_005c4480) to free the memory.

// Forward declarations for the callees (actual names unknown)
void __thiscall SomeClass::destructor(void); // FUN_00985830
void __cdecl operatorDelete(void* ptr);      // FUN_005c4480 (likely custom deallocator)

void __thiscall SomeClass::scalarDeletingDestructor(byte flags) {
    // Call the actual destructor
    this->destructor();

    // If the "delete" flag is set, deallocate the memory
    if (flags & 1) {
        operatorDelete(this);
    }
}