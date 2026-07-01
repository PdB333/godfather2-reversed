// FUNC_NAME: DebugMenu::handleInput
void DebugMenu::handleInput(int inputAction)
{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (inputAction == 8) {
    // Move up in debug menu
    FUN_005a04a0("MoveUp",0,&DAT_00d8d668,0);
    local_c = DAT_011304d8;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return;
  }
  if (inputAction == 9) {
    // Move down in debug menu
    FUN_005a04a0("MoveDown",0,&DAT_00d8d668,0);
    local_c = DAT_011304d8;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return;
  }
  iVar1 = FUN_00466840(); // Get confirm/select action
  if (inputAction == iVar1) {
    // Confirm selection
    FUN_005a04a0("UpdateSelection",0,&DAT_00d8d668,0);
    FUN_00960ac0(); // Execute current menu item
    local_c = DAT_01130448;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return;
  }
  iVar1 = FUN_00466860(); // Get cancel/back action
  if (inputAction == iVar1) {
    // Cancel/back
    FUN_00960ac0(); // Execute current menu item (likely back)
    FUN_00402050(&DAT_01130310,0); // Close menu
  }
  return;
}