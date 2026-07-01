// FUNC_NAME: HitSuccessFanfare::show
void __fastcall HitSuccessFanfare::show(int this)
{
  int iVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  char *rankString;
  undefined1 *local_1034;
  undefined4 local_1030;
  undefined4 local_102c;
  code *local_1028;
  undefined1 *local_1024;
  code *local_1018;
  undefined1 local_1014 [4112];
  undefined4 uStack_4;
  
  uStack_4 = 0x90f69a;
  // Play the "gotoAndPlay" animation for the hit success fanfare
  FUN_005a04a0("gotoAndPlay",0,&DAT_00d83810,1,&DAT_00d839c8);
  
  // Check if the player's current mission is valid
  iVar1 = FUN_008ff210(*(undefined4 *)(this + 0x80)); // +0x80 = currentMission
  if (iVar1 == 0) {
    return;
  }
  
  // Check if the game is in a state to show fanfare
  iVar1 = FUN_008fdfd0();
  if (iVar1 == 0) {
    return;
  }
  
  // Begin fanfare display
  FUN_00604be0();
  
  // Get the player's name
  puVar2 = (undefined4 *)FUN_00790610(); // PlayerManager::getPlayerName
  puVar3 = (undefined1 *)*puVar2;
  if (puVar3 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e; // Empty string fallback
  }
  FUN_00604c10(0x6d,puVar3); // Set text field 0x6d (player name)
  
  // Get player's rank and set appropriate rank string
  iVar1 = FUN_00791750(); // Player::getRank
  if (iVar1 == 3) {
    rankString = "{$rank_soldier}";
  }
  else if (iVar1 == 4) {
    rankString = "{$rank_capo}";
  }
  else {
    if (iVar1 != 5) goto LAB_0090f741;
    rankString = "{$rank_underboss}";
  }
  FUN_00604c10(0x72,rankString); // Set text field 0x72 (rank)
  
LAB_0090f741:
  // Check if there's a target family
  iVar1 = FUN_00791540(); // Player::getTargetFamily
  if (iVar1 != 0) {
    // Get the family name
    puVar2 = (undefined4 *)FUN_008be2d0(); // FamilyManager::getFamilyName
    puVar3 = (undefined1 *)*puVar2;
    if (puVar3 == (undefined1 *)0x0) {
      puVar3 = &DAT_0120546e; // Empty string fallback
    }
    FUN_00604c10(0x66,puVar3); // Set text field 0x66 (family name)
    
    // Set the hit success icon
    FUN_004d3b50(iVar1 + 0x8c); // +0x8c = familyIcon
    
    puVar3 = local_1024;
    if (local_1024 == (undefined1 *)0x0) {
      puVar3 = &DAT_0120546e;
    }
    FUN_0090f370(puVar3); // Set additional icon
    
    if (local_1024 != (undefined1 *)0x0) {
      (*local_1018)(local_1024);
    }
  }
  
  // Show the fanfare message
  local_1034 = (undefined1 *)0x0;
  local_1030 = 0;
  local_102c = 0;
  local_1028 = (code *)0x0;
  FUN_006038a0(DAT_012234a4,local_1014,&local_1034,"$fanfare_hitsuccess_02"); // Get localized string
  
  puVar3 = local_1034;
  if (local_1034 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;
  }
  FUN_005a04a0("ShowMessage",0,&DAT_00d83810,3,"$fanfare_hitsuccess_01",puVar3,
               "$fanfare_hitsuccess_03"); // Display the fanfare message
  
  if (local_1034 != (undefined1 *)0x0) {
    (*local_1028)(local_1034);
  }
  
  // End fanfare display
  FUN_00604c00();
  return;
}