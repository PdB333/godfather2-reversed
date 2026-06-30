// FUNC_NAME: PlayerActionableInfo::updateActionableItems
void __thiscall PlayerActionableInfo::updateActionableItems(int thisPtr, int param_2)
{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int local_38;
  undefined **local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18 [16];
  uint uStack_8;
  
  // Get the actionable item list from param_2 (likely a player or entity)
  iVar1 = *(int *)(param_2 + 0xa0); // +0xA0: pointer to actionable item list
  // Get current write index into the output buffer
  iVar4 = **(int **)(thisPtr + 8) * 0x50 + *(int *)(thisPtr + 4); // +0x8: current index pointer, +0x4: buffer base
  uVar7 = 0;
  
  // Iterate through actionable items
  if (*(short *)(iVar1 + 0x44) != 0) { // +0x44: count of actionable items
    local_38 = 0;
    do {
      puVar5 = (undefined4 *)(*(int *)(iVar1 + 0x80) + local_38); // +0x80: item array base
      if (*(char *)(puVar5 + 7) == '\0') {
        // If item is not animated, use stored value
        uVar6 = puVar5[5]; // +0x14: some ID or hash
      }
      else {
        // If item is animated, call virtual function to get current state
        (**(code **)(*(int *)*puVar5 + 0x34))((int *)*puVar5, local_18); // vtable+0x34: getAnimationState
        uVar6 = uStack_8;
      }
      
      iVar8 = **(int **)(thisPtr + 8) * 0x50 + *(int *)(thisPtr + 4);
      iVar2 = (uVar6 / 0x14) * 0xc;
      
      // Write actionable item data to output buffer
      FUN_0060b620(iVar2, 0, iVar8, 0x1a); // Copy item type/ID
      FUN_0060b620(iVar2, 0, iVar8 + 0x28, 0x1a); // Copy additional data
      
      **(int **)(thisPtr + 8) = **(int **)(thisPtr + 8) + 1; // Increment write index
      local_38 = local_38 + 0x28; // Move to next item (0x28 bytes per item)
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(ushort *)(iVar1 + 0x44));
  }
  
  // Setup callback context
  local_20 = *(undefined4 *)(thisPtr + 0xc); // +0xC: some callback data
  local_1c = *(undefined4 *)(thisPtr + 0x10); // +0x10: more callback data
  local_2c = &PTR_FUN_00e36554; // Function pointer table
  local_28 = param_2;
  local_24 = iVar4;
  
  // Check if we should call the callback
  if (((*(byte *)(param_2 + 0xb2) & 1) != 0) || // +0xB2: flag bit 0
     (cVar3 = (*(code *)PTR_FUN_00e36554)(), cVar3 == '\0')) {
    FUN_0049d0c0(&LAB_0049cd60, &local_2c); // Callback function
  }
  return;
}