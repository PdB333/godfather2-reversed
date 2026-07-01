// FUNC_NAME: PlayerSM::updateStateTransition
void __fastcall PlayerSM::updateStateTransition(int thisPtr)
{
    int iVar1;
    char cVar2;
    int iVar3;
    byte bVar4;
    byte bVar5;
    byte bVar6;
    float fVar7;
    int *piStack_1c;
    undefined4 local_14[4];
    
    // Check if bit 0x10 in flags is set - if so, skip transition
    if ((*(uint *)(thisPtr + 0x4c) & 0x10) != 0) {
        return;
    }
    
    bVar6 = 0;
    local_14[0] = 0;
    
    // Call virtual function at vtable+0x10 to check some condition
    cVar2 = (**(code **)(**(int **)(thisPtr + 0xc) + 0x10))(0x38523fc3, local_14);
    
    if ((cVar2 != '\0') && (piStack_1c != (int *)0x0)) {
        // Call virtual function at vtable+0xC0 to get some float value
        fVar7 = (float)(**(code **)(*piStack_1c + 0xc0))();
        
        iVar3 = *(int *)(thisPtr + 0x58); // +0x58: target state
        
        if ((*(int *)(thisPtr + 0x50) != iVar3) && (*(int *)(thisPtr + 0x38) != 0)) {
            // +0x34: pointer to some data structure
            iVar1 = **(int **)(thisPtr + 0x34);
            
            // Check various float comparisons with global constants
            if ((float)((uint)(*(float *)(iVar1 + 0x1a0) - DAT_01139820) & DAT_00e44680) <= DAT_00d5efb8) {
                bVar6 = 8;
            }
            
            if (DAT_00d5efb8 < (float)((uint)(*(float *)(iVar1 + 0x1a4) - DAT_01139824) & DAT_00e44680)) {
                bVar5 = 0;
            } else {
                bVar5 = 4;
            }
            
            if (DAT_00d5efb8 < (float)((uint)(*(float *)(iVar1 + 0x1a8) - DAT_01139828) & DAT_00e44680)) {
                bVar4 = 0;
            } else {
                bVar4 = 2;
            }
            
            // Check if all three conditions are met (0xE = 8|4|2)
            if ((byte)(bVar4 | bVar5 | bVar6) == 0xe) goto LAB_009965ee;
        }
        
        if (fVar7 <= (float)DAT_00e44598) goto LAB_009965f1;
    }
    
LAB_009965ee:
    iVar3 = *(int *)(thisPtr + 0x54); // +0x54: alternative target state
    
LAB_009965f1:
    // Check if state needs to change or if force flag is set
    if ((iVar3 != *(int *)(thisPtr + 0x50)) || ((*(byte *)(thisPtr + 0x4c) & 8) == 0)) {
        // Call state transition function with new state
        FUN_00996320(iVar3);
    }
    return;
}