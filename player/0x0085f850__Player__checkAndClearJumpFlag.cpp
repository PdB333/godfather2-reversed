// FUNC_NAME: Player::checkAndClearJumpFlag
void __fastcall Player::checkAndClearJumpFlag(int *thisPtr)
{
  // Check if bit 2 (0x4) of field at +0xC88 (param_1[0x322]) is NOT set
  // AND bit 21 (0x200000) of field at +0xFA8 (param_1[0x3ca]) IS set
  if ((((uint)thisPtr[0x322] >> 2 & 1) == 0) && (((uint)thisPtr[0x3ca] >> 0x15 & 1) != 0)) {
    // Call virtual function at vtable offset 0x290 (method index 0xA4)
    // This is likely a "performJump" or similar action
    (**(code **)(*thisPtr + 0x290))();
    // Clear bit 21 (0x200000) of the flag at +0xFA8
    // This resets the "jump requested" flag
    thisPtr[0x3ca] = thisPtr[0x3ca] & 0xffefffff;
  }
  return;
}