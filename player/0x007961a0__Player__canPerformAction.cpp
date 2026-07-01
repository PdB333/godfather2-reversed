// FUNC_NAME: Player::canPerformAction
char __fastcall Player::canPerformAction(int *this)
{
  char result;
  int actionFlags;
  int actionResult;
  
  // Check if player is in a state that allows actions (vtable call at +0x158)
  result = (*(code (**)(void))(*this + 0x158))();
  if ((result != '\0') &&
     // Check if any of the 4 action slots (offsets +0x40C, +0x410, +0x414, +0x418) are non-zero
     ((((this[0x103] != 0 || (this[0x104] != 0)) || (this[0x105] != 0)) ||
      (this[0x106] != 0)))) {
    // Get action flags from the first non-zero slot
    actionFlags = FUN_00405a80(this + 0x103);
    actionResult = FUN_004025a0(actionFlags);
    if (actionResult != 0) {
      actionResult = FUN_004025a0(actionFlags);
      if (actionResult == 0) {
        return '\x01';
      }
      result = FUN_00402c80();
      if (result != '\0') {
        return '\x01';
      }
    }
    result = '\0';
  }
  return result;
}