// FUNC_NAME: NPC::updateDetectionRange
void __thiscall NPC::updateDetectionRange(int thisPtr, undefined4 param_2, undefined4 param_3)
{
    int iVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    // Check if bit 6 of flags at +0x170 is set
    if ((*(uint *)(thisPtr + 0x170) >> 6 & 1) != 0) {
        // Call some behavior functions (likely related to state update)
        FUN_008faf10(param_2, param_3);
        FUN_008fb220();
    }

    // Get pointer from global + 100 (likely current player or target entity)
    iVar1 = *(int *)(DAT_011298e4 + 100);
    if ((((iVar1 != 0) && (iVar1 != 0x48)) && (*(int *)(thisPtr + 0x160) != 0)) &&
        ((iVar2 = FUN_00471610(), // Get position of something (player/camera)
          fVar3 = *(float *)(iVar1 + 0x6c) - *(float *)(iVar2 + 0x30), // dx
          fVar4 = *(float *)(iVar1 + 0x70) - *(float *)(iVar2 + 0x34), // dy
          fVar5 = *(float *)(iVar1 + 0x74) - *(float *)(iVar2 + 0x38), // dz
          fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3 < *(float *)(thisPtr + 0x378) && // distance squared < detection radius
          (fVar3 = *(float *)(thisPtr + 0x37c), // current distance value
           *(float *)(thisPtr + 0x168) <= fVar3 && fVar3 != *(float *)(thisPtr + 0x168))))) {
        // Update stored max distance within radius
        *(float *)(thisPtr + 0x168) = fVar3;
    }
    return;
}