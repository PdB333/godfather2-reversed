// FUNC_004e0700: callGlobalVtableMethod
void __fastcall callGlobalVtableMethod(void* unusedParam, void* object)
{
    // Call virtual function at offset +4 (second entry) from global vtable pointed by DAT_01194538
    // The call passes 'object' and 0 as arguments
    (**(code (**)(void**))(*DAT_01194538 + 4))(object, 0);
    return;
}