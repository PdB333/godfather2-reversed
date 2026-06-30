// FUNC_NAME: Player::updateDonControlState
undefined1 __fastcall Player::updateDonControlState(int thisPtr)
{
  undefined4 uVar1;
  
  if (*(char *)(thisPtr + 37000) != '\0') {
    // +0x9098: donControlTimer (float)
    *(undefined4 *)(thisPtr + 0x9098) = DAT_00e44620;
    // +0x9094: donControlState (int)
    *(undefined4 *)(thisPtr + 0x9094) = 0;
    uVar1 = DAT_00e2b1a4;
    // +0x909c: donControlDuration (float)
    *(undefined4 *)(thisPtr + 0x909c) = uVar1;
    // +0x90a0: donControlCooldown (float)
    *(undefined4 *)(thisPtr + 0x90a0) = 0;
    // +0x908c: donControlFlags (int)
    *(undefined4 *)(thisPtr + 0x908c) = 0;
    FUN_005eef50(thisPtr);
    // +37000: donControlActive (bool)
    *(undefined1 *)(thisPtr + 37000) = 0;
  }
  return 1;
}