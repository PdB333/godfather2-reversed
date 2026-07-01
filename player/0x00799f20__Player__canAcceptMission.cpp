// FUNC_NAME: Player::canAcceptMission
undefined4 __fastcall Player::canAcceptMission(int thisPtr)
{
  char cVar1;
  
  if ((((*(uint *)(thisPtr + 0x8e0) & 0x1000000) == 0) && // +0x8E0: flags - check NO_ACCEPT_MISSION? (bit 24)
      (((byte)((uint)*(undefined4 *)(thisPtr + 0x8e8) >> 0x1c) & 1) == 0)) && // +0x8E8: another flag - check bit 28?
     ((*(uint *)(thisPtr + 0x8e0) >> 0x17 & 1) == 0)) { // +0x8E0: flags - check DEAD? (bit 23)
    cVar1 = FUN_007f47a0(); // likely isInCutscene() or some blocking state
    if (cVar1 == '\0') {
      return 1; // can accept mission
    }
  }
  return 0; // cannot accept mission
}