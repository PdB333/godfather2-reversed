// FUNC_NAME: EARSObject::addVTableEntry
// Function address: 0x004e5960
// Role: Adds the current class's vtable pointer to the object's vtable table (offset +0x14) and advances the table pointer, then calls the base class initializer.

void __thiscall EARSObject::addVTableEntry(
    void* initArg1, void* initArg2, void* initArg3, void* initArg4, void* initArg5)
{
    // 'this' is a pointer to the derived object, its first field points to a vtable table structure
    uint8_t* pTable = *(uint8_t**)(this);   // dereference this to get the vtable table base

    // Offset 0x14: pointer to the current slot in the vtable pointer array
    void*** ppCurrentSlot = (void***)(pTable + 0x14);
    // Write the class-specific vtable pointer into the current slot
    **ppCurrentSlot = &g_ClassVTable;   // PTR_LAB_01124b08 -> g_ClassVTable

    // Advance the slot pointer by one pointer size (4 bytes)
    *ppCurrentSlot = *ppCurrentSlot + 1;

    // Call the base class initializer with the remaining arguments
    FUN_004e8760(initArg1, initArg2, initArg3, initArg4, initArg5);
}