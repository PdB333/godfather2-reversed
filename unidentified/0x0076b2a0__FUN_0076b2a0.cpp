// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int thisPtr)
{
    undefined4 uVar1;
    char cVar2;
    undefined4 uVar3;
    int *piVar4;
    
    // Check if the object at +0x70 is non-null and not a specific type (0x48)
    if ((*(int *)(thisPtr + 0x70) != 0) && (*(int *)(thisPtr + 0x70) != 0x48)) {
        // If the object at +0x70 is zero, set pointer to null
        if (*(int *)(thisPtr + 0x70) == 0) {
            piVar4 = (int *)0x0;
        }
        else {
            // Otherwise, adjust pointer by subtracting 0x48 (likely a vtable offset)
            piVar4 = (int *)(*(int *)(thisPtr + 0x70) + -0x48);
        }
        // Call a virtual method at vtable+0x10 with a specific hash (0x383225a1)
        cVar2 = (**(code **)(*piVar4 + 0x10))(0x383225a1);
        if ((cVar2 != '\0') && (&stack0x00000000 != &DAT_00000004)) {
            // Retrieve a value from +0x5c offset, then at +0x1ed4
            uVar1 = *(undefined4 *)(*(int *)(thisPtr + 0x5c) + 0x1ed4);
            uVar3 = FUN_00806440();
            FUN_008d8050(uVar1, uVar3);
        }
    }
    return;
}