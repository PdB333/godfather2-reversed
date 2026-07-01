// FUNC_NAME: DebugMenu::handleInput
undefined4 DebugMenu::handleInput(int inputKey)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (inputKey == 8) {
    // Backspace key - move selection up
    FUN_005a04a0("MoveSelectionUp",0,&DAT_00d8a0dc,0);
    local_c = DAT_011302b0;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return 0;
  }
  if (inputKey == 9) {
    // Tab key - toggle debug menu
    FUN_00937020();
    return 0;
  }
  iVar1 = FUN_00466840();
  if (inputKey == iVar1) {
    // Enter key - select current item
    FUN_009372f0();
    return 0;
  }
  iVar1 = FUN_00466860();
  if (inputKey == iVar1) {
    // Escape key - close debug menu
    FUN_00937060();
  }
  return 0;
}