// FUNC_NAME: DebugKeyboardHandler::handleMoveUpDown
int DebugKeyboardHandler::handleMoveUpDown(int direction)
{
  // direction: 8 = MoveUp, 9 = MoveDown
  if (direction == 8) {
    FUN_005a04a0("MoveUp", 0, &DAT_00d84448, 0);
  }
  else if (direction == 9) {
    FUN_005a04a0("MoveDown", 0, &DAT_00d84448, 0);
  }
  else {
    return 0;
  }
  
  // Call a function with a global state pointer (likely debug menu state)
  // +0x00: some state/context pointer
  undefined4 local_c = DAT_011301c0;  // global debug state
  FUN_00408a00(&local_c, 0);
  return 0;
}