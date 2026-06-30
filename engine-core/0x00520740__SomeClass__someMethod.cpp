// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int thisPtr, int param2)
{
    char cVar1;
    undefined **local_14;
    int local_10;
    int local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    // Check if some flag at offset +0xC is zero
    if (*(char *)(thisPtr + 0xc) == '\0') {
        // Setup local variables for a function call
        local_8 = *(undefined4 *)(thisPtr + 0x10);  // +0x10: some value
        local_c = thisPtr + 0x18;                    // +0x18: pointer to data
        local_4 = *(undefined4 *)(thisPtr + 0x14);  // +0x14: another value
        local_14 = &PTR_FUN_00e38384;                // Function pointer table
        local_10 = param2;                           // Second parameter
        
        // Check bit 0 at offset +0xB2 in param2, or call function pointer
        if (((*(byte *)(param2 + 0xb2) & 1) != 0) ||
           (cVar1 = (*(code *)PTR_FUN_00e38384)(), cVar1 == '\0')) {
            // Call another function with a reference to local_14
            FUN_0049d0c0(&LAB_0049cd60, &local_14);
        }
    }
    return;
}