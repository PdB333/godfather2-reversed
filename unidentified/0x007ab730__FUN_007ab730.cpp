// FUNC_NAME: SomeManager::checkAndProcessCondition
void __fastcall SomeManager::checkAndProcessCondition(int thisPtr)
{
    int iVar1;
    char cVar2;
    int *piVar3;
    int local_4;

    // Get pointer from this+0x58, then dereference offset 0x1c78
    iVar1 = *(int *)(*(int *)(thisPtr + 0x58) + 0x1c78);
    if ((iVar1 != 0) && (iVar1 != 0x48)) {
        // Re-read (redundant in decompiled code)
        iVar1 = *(int *)(*(int *)(thisPtr + 0x58) + 0x1c78);
        if (iVar1 == 0) {
            piVar3 = (int *)0x0;
        }
        else {
            // Subtract 0x48 to get base of containing structure
            piVar3 = (int *)(iVar1 + -0x48);
        }
        local_4 = 0;
        // Call virtual function at vtable+0x10 with a constant hash (0x55859efa)
        cVar2 = (**(code **)(*piVar3 + 0x10))(0x55859efa);
        // The second condition (&stack0x00000000 != &DAT_00000004) is always true; ignore
        if (cVar2 != '\0') {
            // Call another function with the subobject and address of local_4
            FUN_008d8100(*(int *)(thisPtr + 0x58), &local_4);
        }
    }
    return;
}