// FUNC_NAME: CombatManager::updateDefensiveActions
void __fastcall CombatManager::updateDefensiveActions(int this)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Clear defensive action timer (or flag) at +0x58
  *(undefined4 *)(this + 0x58) = 0;
  
  // Copy defensive action data from parent/owner object at +0x6c
  // +0x50 = copy from owner+0x58
  // +0x54 = copy from owner+0x64 (100 decimal)
  *(undefined4 *)(this + 0x50) = *(undefined4 *)(*(int *)(this + 0x6c) + 0x58);
  *(undefined4 *)(this + 0x54) = *(undefined4 *)(*(int *)(this + 0x6c) + 100);
  
  // Call internal update function
  FUN_00937920();
  
  // Log update event with debug name "UpdateDefensiveActions"
  FUN_005a04a0("UpdateDefensiveActions", 0, &DAT_00d8a1e4, 0);
  
  // Setup local variables for some operation
  local_c = DAT_01130478;
  local_8 = 0;
  local_4 = 0;
  
  // Call some initialization/reset function
  FUN_00408a00(&local_c, 0);
  
  // Update targeting or AI state (arg0=0, arg1=1)
  FUN_00922e20(0, 1);
  
  // Update combat behavior
  FUN_00956b00();
  
  return;
}