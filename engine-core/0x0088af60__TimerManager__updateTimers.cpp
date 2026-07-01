// FUNC_NAME: TimerManager::updateTimers
void __thiscall TimerManager::updateTimers(int this, int *timerList, char param_3, undefined4 param_4)
{
  uint uVar1;
  int iVar2;
  uint **ppuVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  undefined *puVar7;
  uint uVar8;
  uint local_20;
  uint *local_18;
  undefined *local_14;
  uint *local_10;
  undefined *local_c;
  
  // Decrement timer counter at offset +0x12
  *(short *)((int)timerList + 0x12) = *(short *)((int)timerList + 0x12) + -1;
  if (*(short *)((int)timerList + 0x12) == 0) {
    // Timer expired
    if ((char)param_4 != '\0') {
      iVar2 = FUN_00486770(timerList + 1);  // Check if timer callback exists
      if (iVar2 < 0) {
        FUN_004866e0(timerList + 1);  // Remove timer callback
      }
    }
    if (this == 0) {
      this = 0;
    }
    else {
      this = this + 0x3c;  // Offset to timer data
    }
    FUN_004035f0(timerList[1],4,this);  // Call timer callback
    if ((param_3 != '\0') && (iVar2 = FUN_004025a0(timerList[1]), iVar2 != 0)) {
      FUN_004048c0(iVar2,0);  // Reset timer
    }
    timerList[1] = 0;  // Clear timer reference
    if ((*(byte *)(timerList + 4) & 1) == 0) {
      timerList[3] = 0;  // Clear timer data
    }
  }
  // Process child timers from hash table
  uVar5 = (*(byte *)(*timerList + 10) & 1) + (uint)*(byte *)(*timerList + 8);
  local_20 = 0;
  puVar7 = PTR_DAT_00e541fc;  // Hash table base pointer
  uVar8 = DAT_00e54200;  // Hash table size
  if (uVar5 != 0) {
    do {
      uVar1 = **(uint **)(*(int *)(*timerList + 0x10) + local_20 * 4);  // Get timer ID
      uVar6 = uVar1 % uVar8;  // Hash to bucket
      for (puVar4 = *(uint **)(puVar7 + uVar6 * 4); puVar4 != (uint *)0x0;
          puVar4 = (uint *)puVar4[7]) {  // Traverse bucket chain
        if (uVar1 == *puVar4) {  // Found matching timer
          local_18 = puVar4;
          local_14 = puVar7 + uVar6 * 4;
          ppuVar3 = &local_18;
          goto LAB_0088b063;
        }
      }
      local_c = puVar7 + uVar8 * 4;
      local_10 = *(uint **)(puVar7 + uVar8 * 4);
      ppuVar3 = &local_10;
LAB_0088b063:
      if ((*ppuVar3 != *(uint **)(puVar7 + uVar8 * 4)) &&
         (puVar4 = *ppuVar3 + 1, puVar4 != (uint *)0x0)) {
        FUN_0088af60(puVar4,1,param_4);  // Recursively update child timer
        puVar7 = PTR_DAT_00e541fc;
        uVar8 = DAT_00e54200;
      }
      local_20 = local_20 + 1;
    } while (local_20 < uVar5);
  }
  return;
}