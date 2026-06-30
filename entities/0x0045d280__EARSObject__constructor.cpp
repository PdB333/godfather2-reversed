// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(int* thisPtr, int param2, long long param3, int param4) {
    // First member (+0x00) is a self-pointer to the actual object
    int objectBase = *thisPtr;

    // Set vtable pointer at offset +0x14
    // The global label PTR_LAB_0110b974 points to the start of a vtable (including RTTI)
    void** vtableSlot = (void**)(objectBase + 0x14);
    *vtableSlot = (void**)&PTR_LAB_0110b974;  // point to vtable base
    *vtableSlot = (void**)((char*)*vtableSlot + 4); // skip first entry (RTTI)

    // Call the real initializer
    FUN_00461a30(param2, param3, param4);
}