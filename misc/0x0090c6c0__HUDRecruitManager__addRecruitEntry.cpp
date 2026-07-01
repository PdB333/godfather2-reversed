// FUNC_NAME: HUDRecruitManager::addRecruitEntry
void __thiscall HUDRecruitManager::addRecruitEntry(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  int local_74;
  undefined1 *local_70 [3];
  code *local_64;
  undefined1 local_60 [16];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  // Format the HUD string key: "hud_recruit_%s_%u" with param_5 and (this+0x18)+1
  FUN_004d4a60(local_70, 1, "hud_recruit_%s_%u", param_5, *(int *)(this + 0x18) + 1);
  
  // Get some global state (likely current screen resolution or UI dimensions)
  iVar2 = FUN_00471610();
  local_20 = *(undefined4 *)(iVar2 + 0x30);
  local_1c = *(undefined4 *)(iVar2 + 0x34);
  local_18 = *(undefined4 *)(iVar2 + 0x38);
  
  // Initialize color/alpha values from global constants
  local_50 = _DAT_00d5780c;  // +0x00: color RGBA or similar
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = _DAT_00d5780c;  // +0x10: another color
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = _DAT_00d5780c;  // +0x20: another color
  local_24 = 0;
  local_14 = _DAT_00d5780c;  // +0x30: another color
  
  puVar3 = local_70[0];
  if (local_70[0] == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;  // Fallback empty string
  }
  
  // Set the HUD text
  FUN_004eacb0(puVar3);
  
  // Create the HUD entry widget
  FUN_004df420(&local_74, local_60, &local_50, param_3, 0, param_2, 0xffffffff, param_4);
  
  // Insert into linked list at (this + index*4) where index = this+0x18
  iVar2 = *(int *)(this + *(int *)(this + 0x18) * 4);
  piVar1 = (int *)(this + *(int *)(this + 0x18) * 4);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 8) = 0;
    *piVar1 = 0;
  }
  *piVar1 = local_74;
  if (local_74 != 0) {
    *(int **)(local_74 + 8) = piVar1;
  }
  
  // Increment entry count
  *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
  
  // Free the formatted string if allocated
  if (local_70[0] != (undefined1 *)0x0) {
    (*local_64)(local_70[0]);
  }
  return;
}