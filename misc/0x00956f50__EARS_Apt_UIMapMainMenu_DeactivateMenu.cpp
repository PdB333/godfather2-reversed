// Xbox PDB: EARS_Apt_UIMapMainMenu_DeactivateMenu
// FUNC_NAME: PlayerActionableTargetSM::deactivateTarget
void __fastcall PlayerActionableTargetSM::deactivateTarget(int thisPtr)
{
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_10;
  undefined1 local_f;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Check if target is active (+0x50 = active flag)
  if (*(char *)(thisPtr + 0x50) != '\0') {
    // Set hasTarget flag (+0x51) based on target entity (+0x6c)
    *(bool *)(thisPtr + 0x51) = *(int *)(thisPtr + 0x6c) != 0;
    // Clear active flag
    *(undefined1 *)(thisPtr + 0x50) = 0;
    
    // Send "Deactivate" event
    FUN_005a04a0("Deactivate", 0, &DAT_00d8c174, 0);
    
    // Stop targeting state machine
    FUN_00957e10();
    
    // Remove state machine transitions
    FUN_005c0d50(thisPtr + 0x14, &LAB_005bfc10, 0);
    FUN_005c0d30();
    FUN_005c0d50(thisPtr + 0x14, &LAB_005bfbe0, 0);
    
    // Clear targeting data
    FUN_00977250();
    
    local_c = DAT_01130298;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);
    
    // Decrement retry count if active (+0x78)
    if (0 < *(int *)(thisPtr + 0x78)) {
      *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + -1;
    }
    
    // If no target entity, switch to activate button
    if (*(int *)(thisPtr + 0x6c) == 0) {
      local_14 = 0x31; // '1' - deactivate button
      local_13 = 0;
      FUN_005a04a0("DeactivateButton", 0, &DAT_00d8c174, 1, &local_14);
      
      FUN_0097b630(1, 0); // Enable activate button
      *(undefined1 *)(thisPtr + 0x7c) = 0;
      
      local_10 = 0x30; // '0' - activate button
      local_f = 0;
      FUN_005a04a0("ActivateButton", 0, &DAT_00d8c174, 1, &local_10);
    }
  }
  return;
}