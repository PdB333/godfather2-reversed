// FUNC_NAME: SomeEARSObject::setupVTable
void __thiscall SomeEARSObject::setupVTable(int *this, int param2, int param3, uint64 param4, uint64 param5, int param6, int param7, int param8)
{
    int *vtablePtr;
    int *ppVtableSlot;

    // Dereference 'this' to get the internal object pointer (likely a handle or offset)
    vtablePtr = (int *)*this;  // +0x00: pointer to the actual object

    // Write the address of the static vtable pointer into the vtable table at offset 0x14
    // This sets up the virtual function table for this class
    *(int **)(vtablePtr + 0x14 / 4) = (int *)&PTR_LAB_01124ff8;  // +0x14: vtable entry

    // Advance the internal vtable pointer (vtablePtr+0x14) by 4 bytes (one slot)
    // This is typical for chaining vtable updates in class hierarchies
    ppVtableSlot = (int *)(vtablePtr + 0x14 / 4);
    *ppVtableSlot = (int)((char *)*ppVtableSlot + 4);

    // Call the next initializer with all remaining parameters
    FUN_005085d0(param2, param3, param4, param5, param6, param7, param8);
}