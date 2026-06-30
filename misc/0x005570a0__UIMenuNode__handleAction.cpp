// FUNC_NAME: UIMenuNode::handleAction
void __thiscall UIMenuNode::handleAction(undefined4 param_1)
{
    int someValue;
    int *globalObjectPtr;
    undefined4 result;
    char *strPtr;
    int iVar4;
    undefined4 localStructPart1;
    undefined4 localStructPart2;
    undefined4 localStructPart3;
    undefined4 localStructPart4;
    undefined1 localBuffer1[12];
    undefined1 localBuffer2[12];
    undefined4 localVar1;
    undefined4 localVar2;
    undefined4 localVar3;
    undefined4 localVar4;
    undefined4 localVar5;
    undefined1 localBuffer3[8];
    undefined4 localVar6;

    localVar1 = 0;
    localVar2 = 0;
    localVar3 = 0;
    localVar6 = DAT_00e2b1a4;  // Global constant or object reference

    // Call virtual method at vtable+0x90: copy? (destination, source, count)
    (**(code **)(**(int **)(this + 0x44) + 0x90))(localBuffer2, this + 0x48, 1);

    localStructPart1 = localVar4;
    localStructPart2 = localVar5;
    localStructPart3 = localVar3;
    localStructPart4 = DAT_00e2b1a4;

    // Build a stack structure and call another function
    FUN_004b59d0(auStack_6c, &stack0xffffff54);

    // Member function on this object
    FUN_00aa1fc0(this);

    someValue = *(int *)(this + 0x40);
    if (someValue != 0) {
        // Access global singleton (DAT_0113dfc8) and retrieve a factory object
        globalObjectPtr = (int *)(**(code **)(*DAT_0113dfc8 + 0x14))();
        result = (**(code **)(*globalObjectPtr + 0x10))(someValue);
        strPtr = (char *)FUN_00ab06f0(&stack0xffffff53, result);
        if (*strPtr == '\0') {
            goto label_skipCheck;
        }
    }
    if (*(int *)(this + 0x40) != 0) {
        FUN_009f17c0(&stack0xffffff54);
        return;
    }

label_skipCheck:
    iVar4 = FUN_00556e10();
    if (iVar4 != 0) {
        if (*(int *)(iVar4 + 8) != 0) {
            FUN_00aa3930(&stack0xffffff54);
            FUN_009de610(&localStructPart1, localBuffer3, param_1, iVar4);
            return;
        }
        FUN_009f4cd0(&stack0xffffff54);
    }
    return;
}