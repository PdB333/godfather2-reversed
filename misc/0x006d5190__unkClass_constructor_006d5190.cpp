// FUNC_NAME: unkClass_constructor_006d5190
// Address: 0x006d5190
// Role: Constructor for an unknown class with dual vtable pointers.
//       Calls a base class constructor and conditionally invokes an allocation/placement routine.

class UnidentifiedClass {
public:
    // +0x00: Primary vtable pointer
    void** vtablePrimary;
    // +0x08: Secondary vtable pointer (likely multiple inheritance or interface)
    void** vtableSecondary;
    // Additional members follow, total size at least 0xD0 (208) bytes.
};

// __thiscall: thisPtr in ECX
UnidentifiedClass* __thiscall unkConstructor(UnidentifiedClass* thisPtr, byte allocFlag) {
    // Set vtable pointers for this object
    thisPtr->vtablePrimary = (void**)&PTR_FUN_00d5f3bc;   // First virtual function table
    thisPtr->vtableSecondary = (void**)&PTR_LAB_00d5f3b4; // Second table (e.g., second base or interface)

    // Call base class constructor (likely a virtual or non-virtual base)
    FUN_00473a60();

    // If allocFlag bit 0 is set, perform additional memory setup (possibly placement new or custom allocator)
    if ((allocFlag & 1) != 0) {
        // Retrieve global allocation function table
        int* const allocFuncTable = FUN_009c8f80();
        // Call the function at offset 4 (index 1) in the table with this and size 0xD0
        // This may initialize the object in the given memory block or allocate new memory.
        ((void (*)(UnidentifiedClass*, uint))((uint*)allocFuncTable)[1])(thisPtr, 0xD0);
    }

    return thisPtr;
}