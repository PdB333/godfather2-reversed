// FUNC_NAME: ChaseCamera::updateOrientation
void __thiscall ChaseCamera::updateOrientation(int thisPtr, int targetNode, bool isInitial, undefined4 param_4)
{
    int *piVar1;
    undefined8 *puVar2;
    int iVar3;
    float *pfVar4;
    int iVar5;
    int iVar6;
    bool bVar7;
    float local_28;
    float local_24;
    float local_20;
    undefined8 local_1c;
    float local_14;
    
    // Possibly set camera constants from global globals if initializing
    if (isInitial != '\0') {
        *(undefined4 *)(thisPtr + 0x38) = DAT_00d5f37c;     // +0x38: unknown
        *(undefined4 *)(thisPtr + 0x44) = DAT_00d5f540;     // +0x44: offset
        *(undefined4 *)(thisPtr + 0x54) = DAT_00d5f53c;     // +0x54: offset
        *(undefined4 *)(thisPtr + 0x58) = DAT_00d5d740;     // +0x58: offset
        *(undefined4 *)(thisPtr + 0x5c) = DAT_00d5d934;     // +0x5c: offset
        *(undefined4 *)(thisPtr + 0x4c) = DAT_00d5f538;     // +0x4c: offset
        *(undefined4 *)(thisPtr + 0x50) = DAT_00d5ccf8;     // +0x50: offset
        *(undefined4 *)(thisPtr + 0x74) = DAT_00d5f520;     // +0x74: offset
        *(undefined4 *)(thisPtr + 0x78) = DAT_00d5ef88;     // +0x78: offset
        *(undefined4 *)(thisPtr + 0x84) = 0;                // +0x84: flag
        *(undefined4 *)(thisPtr + 0x80) = 0;                // +0x80: flag
        *(undefined4 *)(thisPtr + 0x7c) = 0;                // +0x7c: flag
    }
    // Free previous node if present
    if (*(int *)(thisPtr + 0x28) != 0) {                    // +0x28: pointer to some object
        FUN_004daf90((undefined4 *)(thisPtr + 0x28));       // free function
        *(undefined4 *)(thisPtr + 0x28) = 0;
    }
    piVar1 = (int *)(thisPtr + 0x30);                       // +0x30: linked list node pointer
    if (targetNode == 0) {
        iVar3 = 0;
    }
    else {
        iVar3 = targetNode + 0x48;                          // offset 0x48 in target node
    }
    if (*piVar1 != iVar3) {
        if (*piVar1 != 0) {
            FUN_004daf90(piVar1);                           // free old node
        }
        *piVar1 = iVar3;
        if (iVar3 != 0) {
            *(undefined4 *)(thisPtr + 0x34) = *(undefined4 *)(iVar3 + 4);  // +0x34: next?
            *(int **)(iVar3 + 4) = piVar1;
        }
    }
    *(undefined4 *)(thisPtr + 0x88) = param_4;              // +0x88: store some parameter
    if (targetNode == 0) {
        // Compute vector from player to some offset
        puVar2 = (undefined8 *)FUN_00424fb0(&local_28, _DAT_00002494);  // get a constant vector (global ID)
        local_1c = *puVar2;
        local_14 = *(float *)(puVar2 + 1);
        iVar3 = FUN_00471610();                              // get player position
        local_28 = *(float *)(iVar3 + 0x30) - (float)local_1c;  // delta X
        local_24 = *(float *)(iVar3 + 0x34) - local_1c._4_4_; // delta Y
        local_20 = *(float *)(iVar3 + 0x38) - local_14;       // delta Z
        pfVar4 = (float *)FUN_00471610();                     // forward direction?
        iVar3 = FUN_00471610();                               // right direction?
        iVar5 = FUN_00471610();                               // up direction?
        bVar7 = *(float *)(iVar3 + 4) * local_24 + *pfVar4 * local_28 + *(float *)(iVar5 + 8) * local_20 < 0.0;
        iVar3 = FUN_00471610();                               // another set of orientation axes
        iVar5 = FUN_00471610();
        iVar6 = FUN_00471610();
        if (*(float *)(iVar5 + 0x24) * local_24 + *(float *)(iVar3 + 0x20) * local_28 +
            *(float *)(iVar6 + 0x28) * local_20 <
            SQRT(local_20 * local_20 + local_24 * local_24 + local_28 * local_28) * _DAT_00d5f534) {
            bVar7 = !bVar7;
        }
        if (bVar7) {
            *(float *)(thisPtr + 0x3c) = DAT_00e44564 - *(float *)(thisPtr + 0x3c);  // flip some angle/offset
        }
    }
    return;
}