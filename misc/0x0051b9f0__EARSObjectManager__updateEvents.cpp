// FUNC_NAME: EARSObjectManager::updateEvents
void EARSObjectManager::updateEvents(int param_2, float param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  undefined4 extraout_ECX;
  uint *puVar7;
  int unaff_FS_OFFSET;
  float fVar8;
  int local_20;
  int local_1c;
  
  // Check if object is paused/disabled (bitmask at +0xc)
  if ((*(uint *)(this + 0xc) & 0x20300000) == 0) {
    // Global speed factor
    fVar8 = *(float *)(*(int *)(this + 0x10) + 0x20) * _DAT_00e44878;
    local_20 = 0;
    // Iterate over children (count at +0x80)
    if (0 < *(short *)(this + 0x80)) {
      local_1c = 0;
      puVar7 = (uint *)(this + 0xf0); // Child data array (20 bytes each)
      do {
        piVar1 = (int *)puVar7[1]; // Child object pointer
        iVar2 = *(int *)(this + 0x10); // Parent object
        // Check child validity and flags
        if ((((piVar1 != (int *)0x0) && ((*puVar7 & 0x4000000) == 0)) &&
            (iVar3 = **(int **)(unaff_FS_OFFSET + 0x2c), // Global state pointer
            (*(uint *)(piVar1[4] + *(int *)(iVar3 + 8)) & 0x20000000) == 0)) &&
           ((((*puVar7 & 0x200000) == 0 && ((~*(byte *)(puVar7[2] + 0xc) & 1) != 0)) &&
            (cVar6 = (**(code **)(*piVar1 + 0xc))(), cVar6 != '\0')))) {
          uVar4 = *puVar7; // Child flags
          uVar5 = *(uint *)(piVar1[4] + *(int *)(iVar3 + 8));
          iVar3 = piVar1[3]; // Child timestamp/ID
          // Call update function
          FUN_00533c90();
          FUN_0051b930(param_2,extraout_ECX,
                       // Build command/type from flags and offsets
                       CONCAT44(fVar8,
                                uVar5 >> 8 & 0x40000 |
                                (int)(short)iVar3 + ((int)uVar4 >> 2 & 0x700U) |
                                (int)uVar4 >> 1 & 0x1000U |
                                uVar4 & 0x120000),
                       *(float *)(iVar2 + local_1c + 0x40) + param_3,
                       (int)*(short *)((int)piVar1 + 0xe));
        }
        local_20 = local_20 + 1;
        local_1c = local_1c + 0x24; // Stride for float array in parent
        puVar7 = puVar7 + 5; // Each child entry is 20 bytes
      } while (local_20 < *(short *)(this + 0x80));
    }
  }
  return;
}