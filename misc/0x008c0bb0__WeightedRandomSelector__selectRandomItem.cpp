// FUNC_NAME: WeightedRandomSelector::selectRandomItem
undefined4 __thiscall FUN_008c0bb0(int this, float threshold, uint maxItems, int *outArray)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  float accumulatedWeight;
  uint index;
  
  accumulatedWeight = *(float *)(this + 0x1b4) * DAT_00d5eee4;
  index = 0;
  if (*(int *)(this + 0x1a8) != 0) {
    do {
      iVar5 = *(int *)(*(int *)(this + 0x1a4) + index * 4);
      cVar3 = FUN_008c8110();  // Check if item is valid/available
      if (cVar3 != '\0') {
        iVar4 = outArray[2];
        uVar2 = *(undefined4 *)(iVar5 + 8);  // Get item ID from +0x08
        if (outArray[1] == iVar4) {
          if (iVar4 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = iVar4 * 2;
          }
          FUN_006b1e10(iVar4);  // Reallocate array
        }
        puVar1 = (undefined4 *)(*outArray + outArray[1] * 4);
        outArray[1] = outArray[1] + 1;
        if (puVar1 != (undefined4 *)0x0) {
          *puVar1 = uVar2;  // Store item ID
        }
        iVar5 = FUN_008c8170();  // Get weight index
        accumulatedWeight = *(float *)(this + 0x1b0 + iVar5 * 4) + accumulatedWeight;
        if (threshold < accumulatedWeight) {
          return 1;
        }
        if (maxItems <= (uint)outArray[1]) break;
      }
      index = index + 1;
    } while (index < *(uint *)(this + 0x1a8));
  }
  if (threshold < accumulatedWeight) {
    return 1;
  }
  return 0;
}