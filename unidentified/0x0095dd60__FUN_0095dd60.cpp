// FUNC_NAME: SomeClass::getLocalizedStrings
void __thiscall SomeClass::getLocalizedStrings(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
    undefined1 *stringPtr;
    undefined1 *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;

    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    
    // Get string from first resource ID at offset +0x14
    FUN_00604000(*(undefined4 *)(thisPtr + 0x14), &local_10, 1);
    stringPtr = local_10;
    if (local_10 == (undefined1 *)0x0) {
        stringPtr = &DAT_0120546e; // Default empty string
    }
    FUN_005c4660(param2, stringPtr, param5, local_c);
    
    // Get string from second resource ID at offset +0x44
    FUN_00603d30(*(undefined4 *)(thisPtr + 0x44), &local_10, 1);
    stringPtr = local_10;
    if (local_10 == (undefined1 *)0x0) {
        stringPtr = &DAT_0120546e; // Default empty string
    }
    FUN_005c4660(param3, stringPtr, param5, local_c);
    
    // Get string from third resource ID at offset +0x48
    FUN_00603d30(*(undefined4 *)(thisPtr + 0x48), &local_10, 1);
    stringPtr = local_10;
    if (local_10 == (undefined1 *)0x0) {
        stringPtr = &DAT_0120546e; // Default empty string
    }
    FUN_005c4660(param4, stringPtr, param5, local_c);
    
    if (local_10 != (undefined1 *)0x0) {
        (*local_4)(local_10); // Cleanup if allocated
    }
    return;
}