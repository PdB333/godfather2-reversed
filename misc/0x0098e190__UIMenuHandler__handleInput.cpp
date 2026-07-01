// FUNC_NAME: UIMenuHandler::handleInput
undefined4 __thiscall UIMenuHandler::handleInput(int *this, int actionId)
{
  int result;
  char *moveString;

  result = FUN_00466840(); // GetConfirmActionID? (e.g., confirm/select)
  if (actionId == result) {
    FUN_00402050(&DAT_01130448,0); // Play sound or set state for confirm
    FUN_0098db20(); // Possibly execute selection
    return 0;
  }

  result = FUN_00466860(); // GetCancelActionID? (e.g., cancel/back)
  if (actionId == result) {
    FUN_00402050(&DAT_01130310,0); // Play sound or set state for cancel
    (*(code **)(*this + 0x2c))(); // Call virtual method at vtable+0x2c (e.g., onCancel)
    if ((code *)this[0x24] != (code *)0x0) { // this+0x90 (if int*)
      (*(code *)this[0x24])(this); // Call custom callback at this[0x24]
      return 0;
    }
  }
  else {
    if (actionId == 8) { // Up arrow?
      if ((uint)this[0x25] <= (uint)this[0x1d]) { // this[0x94] <= this[0x74]? (current index vs min)
        return 0;
      }
      if (this[0x20] == 0) { // this[0x80] (some flag)
        return 0;
      }
      moveString = "MoveUp";
    }
    else {
      if (actionId != 9) { // Down arrow?
        return 0;
      }
      if (this[0x20] == 0) {
        return 0;
      }
      moveString = "MoveDown";
    }
    FUN_005a04a0(moveString,0,&DAT_00e3d7ac,0); // Send UI navigation command
    FUN_00402050(&DAT_011301c0,0); // Play sound for move
  }
  return 0;
}