// FUNC_NAME: BaseObject::setupVTable
void __thiscall BaseObject::setupVTable(int* thisPtr,
                                        undefined4 param2, undefined4 param3, undefined4 param4,
                                        undefined8 param5, undefined4 param6, undefined8 param7,
                                        undefined4 param8, undefined8 param9, undefined4 param10,
                                        undefined4 param11)
{
    // Dereference the object's vtable pointer (first 4 bytes of the object)
    int* vtableBase = *thisPtr; // vtableBase points to the beginning of the virtual function table

    // At offset +0x14 in the vtable, there is a pointer to a table of function pointers
    // Set the current function pointer entry to the address of PTR_FUN_01124654
    **(int**)(vtableBase + 0x14) = (int)&PTR_FUN_01124654;

    // Advance the table pointer by 4 bytes (one function pointer)
    int** tablePtr = (int**)(vtableBase + 0x14);
    *tablePtr = *tablePtr + 1;

    // Delegate to the actual initialization/constructor function with all remaining parameters
    // FUN_004b91f0 likely performs further object construction (e.g., member initialization)
    FUN_004b91f0(param2, param3, param4, param5, param6, param7, param8, param9, param10, param11);
}