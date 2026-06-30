// FUNC_NAME: EARSObject::installVtableEntry
void __thiscall EARSObject::installVtableEntry(void* param_2, void* param_3, void* param_4, void* param_5, unsigned int param_6, unsigned int param_7)
{
    // Dereference 'this' to get the internal pointer (likely a vtable/initialization context)
    int* internalPtr = *(int**)this; // *param_1

    // Write the function pointer (global constant) into the vtable slot at offset 0x14 (5th entry, 4 bytes each)
    *(void**)(internalPtr + 0x14) = (void*)&PTR_FUN_01123cb0; // +0x14: vtable slot

    // Move the pointer at offset 0x14 by 4 bytes to point to the next slot
    int** nextSlot = (int**)(internalPtr + 0x14);
    *nextSlot = *nextSlot + 4;

    // Call the common initialization/setup function with 1 as a flag
    FUN_0048e330(param_2, param_3, param_4, param_5, param_6, param_7, 1);
}