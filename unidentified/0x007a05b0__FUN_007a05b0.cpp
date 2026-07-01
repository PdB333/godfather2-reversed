// FUNC_NAME: SomeClass::createAndRegisterObject
void __fastcall SomeClass::createAndRegisterObject(undefined4 param_1)
{
    char cVar1;
    int iVar2;
    int iVar3;
    undefined4 *puVar4;
    undefined4 *puVar5;

    // Check if some global condition is met (likely a game state flag)
    cVar1 = FUN_00481660();
    if (cVar1 != '\0') {
        // Allocate memory for an object of size 0x78 (120 bytes)
        iVar2 = FUN_009c8e50(0x78);
        if (iVar2 == 0) {
            iVar2 = 0;
        }
        else {
            // Initialize the object with the given parameter
            iVar2 = FUN_007a0440(param_1);
        }
        // Copy 0x10 (16) dwords (64 bytes) from the stack to the object at offset +0x38
        puVar4 = (undefined4 *)&stack0x00000004;
        puVar5 = (undefined4 *)(iVar2 + 0x38);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
        }
        // Register the object (likely add to a manager or list)
        FUN_00481690(iVar2);
    }
    return;
}