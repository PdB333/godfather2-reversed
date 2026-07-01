// FUNC_NAME: Player::handleInputEvent
void __thiscall Player::handleInputEvent(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  // Check if input is not disabled (bit 8 of flags at +0x8ec) and if there's an active input handler at +0x1bc8
  if (((*(uint *)(this + 0x8ec) >> 8 & 1) == 0) && (*(int *)(this + 0x1bc8) != 0)) {
    // Forward the input event to the active input handler (likely a state machine or controller component)
    FUN_007ef230(*(undefined4 *)(this + 0x1bc4), param_2, param_3, param_4, param_5);
    // Reset some input state after processing
    FUN_007f04d0(0);
  }
  return;
}