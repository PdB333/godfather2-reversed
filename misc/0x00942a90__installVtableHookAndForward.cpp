// FUNC_NAME: installVtableHookAndForward

void __thiscall installVtableHookAndForward(void* this, int* param2, int param3)
{
    int field0 = param2[0];    // first field
    int field3 = param2[3];    // fourth field
    int field1 = param2[1];    // second field
    int field2 = param2[2];    // third field

    // Global structure at 0x01206880, offset +0x14 is a pointer to a vtable pointer table
    int** vtableTable = (int**)(*(int*)(0x01206880 + 0x14));  // DAT_01206880 + 0x14
    *vtableTable = &PTR_FUN_00e56974;                         // Hook the current slot
    vtableTable++;                                           // Move to next slot

    // Forward call with reordered arguments: field0, field1, field2, field3, plus the extra param3
    FUN_00941610(this, field0, field1, field2, field3, param3);
}