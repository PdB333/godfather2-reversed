// FUNC_NAME: Player::handleActionInput
uint __thiscall Player::handleActionInput(int this, undefined4 actionId)
{
  uint actionFlags;
  
  actionFlags = *(uint *)(this + 0x249c) >> 1;
  if ((actionFlags & 1) != 0) {
    actionFlags = FUN_00481620(); // likely isPlayerAlive() or similar
    if ((char)actionFlags != '\0') {
      actionFlags = FUN_00466260(*(undefined1 *)(this + 0x2498), actionId); // likely executeAction
      return actionFlags;
    }
  }
  return actionFlags & 0xffffff00;
}