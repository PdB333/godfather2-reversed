// FUNC_NAME: Player::handleInputAction
void __thiscall Player::handleInputAction(int this, undefined4 actionType, undefined4 *resultX, undefined4 *resultY)
{
  char isInputAllowed;
  
  // Check if input is enabled (bit 1 of some flags at offset +0x249c)
  if ((*(uint *)(this + 0x249c) >> 1 & 1) != 0) {
    isInputAllowed = FUN_00481620(); // likely InputManager::isInputAllowed()
    if (isInputAllowed != '\0') {
      FUN_00465d20(*(undefined1 *)(this + 0x2498),actionType,resultX,resultY); // likely Player::applyInputAction
      return;
    }
  }
  // If input disabled or not allowed, return zero outputs
  *resultY = 0;
  *resultX = 0;
  return;
}