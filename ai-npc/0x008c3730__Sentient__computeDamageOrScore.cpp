// FUNC_NAME: Sentient::computeDamageOrScore
float __thiscall Sentient::computeDamageOrScore(int this, int *damageTypeArray, float multiplier, int *outScoreArray)
{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  float fVar9;
  float local_1c;
  uint local_18;
  int local_10;
  int local_c;
  
  piVar5 = outScoreArray;
  bVar8 = *(int *)(this + 0x54) == 0x637b907; // Check if this is a specific type (e.g., player)
  local_1c = 0.0;
  local_c = 0;
  local_10 = (int)multiplier;
  local_18 = 0;
  if (damageTypeArray[1] != 0) {
    do {
      uVar3 = *(undefined4 *)(*damageTypeArray + local_18 * 4); // Get damage type ID
      iVar6 = FUN_00791750(); // Get damage type index
      fVar9 = 0.0;
      outScoreArray = (int *)_DAT_00d5780c;
      multiplier = 0.0;
      switch(iVar6) {
      case 1: // Damage type 1
        local_10 = local_10 + 1;
        break;
      case 3: // Damage type 3
        outScoreArray = *(int **)(DAT_0112f938 + 200); // +0xC8
        if (bVar8) {
          multiplier = *(float *)(DAT_0112f938 + 0xd8); // +0xD8
        }
        break;
      case 4: // Damage type 4
        outScoreArray = *(int **)(DAT_0112f938 + 0xcc); // +0xCC
        if (bVar8) {
          multiplier = *(float *)(DAT_0112f938 + 0xdc); // +0xDC
        }
        break;
      case 5: // Damage type 5
        outScoreArray = *(int **)(DAT_0112f938 + 0xd0); // +0xD0
        if (bVar8) {
          multiplier = *(float *)(DAT_0112f938 + 0xe0); // +0xE0
        }
      }
      if (iVar6 - 3U < 3) { // Damage types 3, 4, 5
        if ((bVar8) && (iVar7 = FUN_008c1250(uVar3), iVar7 != 0)) { // Check if damage type is valid
          iVar7 = FUN_008c8390(); // Get random value
          local_c = local_c + iVar7;
          iVar7 = FUN_008c8390(); // Get another random value
          fVar9 = (float)iVar7;
          if (iVar7 < 0) {
            fVar9 = fVar9 + DAT_00e44578; // Convert to unsigned
          }
          fVar9 = fVar9 * multiplier; // Apply multiplier
        }
        fVar9 = (*(float *)(this + 0x1b0 + iVar6 * 4) + fVar9) * (float)outScoreArray; // Base damage + random * multiplier
        local_1c = fVar9 + local_1c; // Accumulate total
        if (piVar5 != (int *)0x0) {
          iVar6 = piVar5[2];
          if (piVar5[1] == iVar6) { // Check if array is full
            if (iVar6 == 0) {
              iVar6 = 1;
            }
            else {
              iVar6 = iVar6 * 2; // Double capacity
            }
            FUN_008be050(iVar6); // Resize array
          }
          pfVar1 = (float *)(*piVar5 + piVar5[1] * 4);
          piVar5[1] = piVar5[1] + 1; // Increment count
          if (pfVar1 != (float *)0x0) {
            *pfVar1 = fVar9; // Store damage value
          }
        }
      }
      local_18 = local_18 + 1;
      multiplier = (float)local_10;
    } while (local_18 < (uint)damageTypeArray[1]); // Loop through all damage types
  }
  fVar9 = 0.0;
  damageTypeArray = (int *)0x0;
  if ((((bVar8) && (**(int **)(DAT_012233a0 + 4) != 0)) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) // Check for specific game state
     && (iVar6 = FUN_0043b870(DAT_01131010), fVar9 = (float)damageTypeArray, iVar6 != 0)) { // Get player data
    local_c = *(int *)(iVar6 + 0x1c) + local_c; // Add player-specific modifier
    fVar9 = (float)local_c;
    if (local_c < 0) {
      fVar9 = fVar9 + DAT_00e44578;
    }
    fVar9 = fVar9 * *(float *)(DAT_0112f938 + 0xd4); // Apply global multiplier
  }
  fVar4 = (float)(int)multiplier;
  if ((int)multiplier < 0) {
    fVar4 = fVar4 + DAT_00e44578;
  }
  fVar2 = *(float *)(this + 0x1b4); // Base value
  if (piVar5 != (int *)0x0) {
    for (; multiplier != 0.0; multiplier = (float)((int)multiplier + -1)) {
      iVar6 = piVar5[2];
      if (piVar5[1] == iVar6) {
        if (iVar6 == 0) {
          iVar6 = 1;
        }
        else {
          iVar6 = iVar6 * 2;
        }
        FUN_008be050(iVar6);
      }
      pfVar1 = (float *)(*piVar5 + piVar5[1] * 4);
      piVar5[1] = piVar5[1] + 1;
      if (pfVar1 != (float *)0x0) {
        *pfVar1 = fVar9 / fVar4 + fVar2; // Average + base
      }
    }
  }
  return (float10)(fVar2 * fVar4 + fVar9 + local_1c); // Total = base*count + random + accumulated
}