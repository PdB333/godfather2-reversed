// FUNC_NAME: SomeManager::getCurrentOrNextItem
undefined4 * __thiscall SomeManager::getCurrentOrNextItem(int this, undefined4 *outParam, undefined4 param3)
{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined **local_60 [19];
  undefined4 local_14;
  
  if (*(int *)(this + 0xc) == 0) {
    // No items available, call default handler
    FUN_008334a0();
  }
  else {
    if (*(int *)(this + 0xc) == 1) {
      // Only one item, return it directly
      iVar4 = **(int **)(this + 8);
      FUN_0081f9f0(iVar4);
      *outParam = &PTR_LAB_00d73448;
      outParam[0x13] = *(undefined4 *)(iVar4 + 0x4c);
      return outParam;
    }
    // Find index of param3 in the list
    uVar3 = FUN_0082c690(param3);
    if (uVar3 != 0xffffffff) {
      *(uint *)(this + 4) = uVar3;
      // Determine next index (wrap around)
      if (uVar3 < *(int *)(this + 0xc) - 1U) {
        iVar4 = uVar3 + 1;
      }
      else {
        iVar4 = 0;
      }
      iVar1 = *(int *)(*(int *)(this + 8) + uVar3 * 4);
      iVar4 = *(int *)(*(int *)(this + 8) + iVar4 * 4);
      // Check if next item is valid
      cVar2 = FUN_00835a00(param3, iVar4 + 4);
      if (cVar2 != '\0') {
        iVar4 = iVar1;
      }
      FUN_00825150(iVar4);
      return outParam;
    }
    // Fallback if not found
    FUN_008334a0();
  }
  // Default return for empty case
  local_14 = 0;
  local_60[0] = &PTR_LAB_00d73448;
  FUN_0081f9f0(local_60);
  *outParam = &PTR_LAB_00d73448;
  outParam[0x13] = local_14;
  return outParam;
}