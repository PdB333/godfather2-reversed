// FUNC_NAME: HashTable::traverseAndUpdate
void FUN_0088acb0(int *param_1, int param_2)
{
  uint uVar1;
  uint **ppuVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  undefined *puVar8;
  float fVar9;
  uint *local_10;
  undefined *local_c;
  uint *local_8;
  undefined *local_4;
  
  // Get number of entries from hash table header (byte at offset +10 masked with 1, plus byte at +8)
  uVar3 = (*(byte *)(*param_1 + 10) & 1) + (uint)*(byte *)(*param_1 + 8);
  uVar6 = 0;
  uVar7 = DAT_00e54200; // Hash table size
  puVar8 = PTR_DAT_00e541fc; // Hash table bucket array pointer
  if (uVar3 != 0) {
    do {
      // Get hash key from entry list (param_1+0x10 is array of pointers to entries)
      uVar1 = **(uint **)(*(int *)(*param_1 + 0x10) + uVar6 * 4);
      uVar4 = uVar1 % uVar7; // Hash bucket index
      // Search bucket chain for matching key
      for (puVar5 = *(uint **)(puVar8 + uVar4 * 4); puVar5 != (uint *)0x0;
          puVar5 = (uint *)puVar5[7]) {
        if (uVar1 == *puVar5) {
          local_10 = puVar5;
          local_c = puVar8 + uVar4 * 4;
          ppuVar2 = &local_10;
          goto LAB_0088ad1e;
        }
      }
      // Not found, use sentinel at end of bucket array
      local_4 = puVar8 + uVar7 * 4;
      local_8 = *(uint **)(puVar8 + uVar7 * 4);
      ppuVar2 = &local_8;
LAB_0088ad1e:
      // If found and has next pointer (offset +4), recurse
      if ((*ppuVar2 != *(uint **)(puVar8 + uVar7 * 4)) &&
         (puVar5 = *ppuVar2 + 1, puVar5 != (uint *)0x0)) {
        FUN_0088acb0(puVar5, param_2 + 1);
        uVar7 = DAT_00e54200;
        puVar8 = PTR_DAT_00e541fc;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar3);
  }
  // Lookup param_1[1] (some ID) in another hash table at DAT_0122337c + 0x50
  uVar7 = param_1[1];
  puVar5 = *(uint **)(*(int *)(DAT_0122337c + 0x50) + (uVar7 % *(uint *)(DAT_0122337c + 0x54)) * 4);
  if (puVar5 != (uint *)0x0) {
    while (*puVar5 != uVar7) {
      puVar5 = (uint *)puVar5[2];
      if (puVar5 == (uint *)0x0) {
        return;
      }
    }
    // Check if found entry has valid data (offset +4 non-zero) and some condition at +0x24 == 0
    if (((puVar5 != (uint *)0x0) && (puVar5[1] != 0)) && (*(int *)(puVar5[1] + 0x24) == 0)) {
      // Re-search for same key (redundant)
      for (puVar5 = *(uint **)(*(int *)(DAT_0122337c + 0x50) +
                              (uVar7 % *(uint *)(DAT_0122337c + 0x54)) * 4); puVar5 != (uint *)0x0;
          puVar5 = (uint *)puVar5[2]) {
        if (*puVar5 == uVar7) {
          if ((puVar5 != (uint *)0x0) && (puVar5[1] != 0)) {
            fVar9 = *(float *)(puVar5[1] + 0x48); // Get float value at offset +0x48
            goto LAB_0088adc2;
          }
          break;
        }
      }
      fVar9 = 0.0;
LAB_0088adc2:
      // Check bit 0 of param_1[4] - if clear, use less-than comparison; if set, use equality
      if ((*(byte *)(param_1 + 4) & 1) == 0) {
        if (param_2 <= (int)fVar9) {
          return;
        }
      }
      else if (param_2 == (int)fVar9) {
        return;
      }
      // Call update function with ID and float value
      FUN_004042e0(uVar7, (float)param_2);
    }
  }
  return;
}