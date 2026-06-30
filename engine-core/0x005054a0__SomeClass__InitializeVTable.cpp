// FUNC_NAME: SomeClass::InitializeVTable
void __thiscall SomeClass::InitializeVTable(void* this, undefined4 param_2, undefined4 param_3, undefined8 param_4, undefined8 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8)
{
    int* basePtr; // pointer to base of object
    int* vtablePtr; // pointer to vtable pointer field

    // Dereference this to get actual object base (this might be a pointer to pointer)
    basePtr = *(int**)this;

    // Set vtable pointer at offset 0x14 to global vtable
    *(void***)(basePtr + 0x14) = &PTR_LAB_01125034; // +0x14: vtable pointer

    // Advance the vtable pointer by 4 (possible iterator or offset adjustment)
    vtablePtr = (int*)(basePtr + 0x14);
    *vtablePtr = *vtablePtr + 4;

    // Call additional initialization function
    FUN_00508680(param_2, param_3, param_4, param_5, param_6, param_7, param_8);

    return;
}