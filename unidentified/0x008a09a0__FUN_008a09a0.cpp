// FUNC_NAME: SomeClass::processMessage
int __thiscall SomeClass::processMessage(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5)
{
    int *piVar1;
    int iVar2;
    int iVar3;
    int local_8;
    undefined4 local_4;
    
    // Allocate 0x60 bytes for a new object
    iVar2 = FUN_009c8e50(0x60);
    if (iVar2 == 0) {
        iVar2 = 0;
    }
    else {
        // Call constructor with parameters
        iVar2 = FUN_0089cf40(param_3, param_4, *(undefined4 *)(this + 200), param_5);
    }
    
    // Clear the pointer at this+200
    *(undefined4 *)(this + 200) = 0;
    
    // Check global flag
    if (DAT_0112a87c != 0) {
        FUN_00928690();
    }
    
    // Handle linked list insertion at this+0xB4
    if (param_5 != 0) {
        piVar1 = (int *)(this + 0xb4);
        if ((*(int *)(this + 0xb4) != 0) && (*(int *)(this + 0xb4) != 0x1c)) {
            if (*piVar1 == 0) {
                iVar3 = 0;
            }
            else {
                iVar3 = *piVar1 + -0x1c;
            }
            FUN_0089fee0(iVar3);
        }
        if (iVar2 == 0) {
            iVar3 = 0;
        }
        else {
            iVar3 = iVar2 + 0x1c;
        }
        if (*piVar1 != iVar3) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1);
            }
            *piVar1 = iVar3;
            if (iVar3 != 0) {
                *(undefined4 *)(this + 0xb8) = *(undefined4 *)(iVar3 + 4);
                *(int **)(iVar3 + 4) = piVar1;
            }
        }
    }
    
    // Setup local linked list node
    if (iVar2 == 0) {
        local_8 = 0;
    }
    else {
        local_8 = iVar2 + 0x1c;
    }
    local_4 = 0;
    if (local_8 != 0) {
        local_4 = *(undefined4 *)(local_8 + 4);
        *(int **)(local_8 + 4) = &local_8;
    }
    
    // Process the message
    FUN_0089fbe0(param_2, &local_8);
    
    // Cleanup local linked list
    if (local_8 != 0) {
        FUN_004daf90(&local_8);
    }
    
    return iVar2;
}