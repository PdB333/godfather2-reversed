// FUNC_NAME: PlayerSM::updateWhoringSkillOrReputation
void __thiscall PlayerSM::updateSkillOrReputation(int this, int param_2)
{
  char cVar1;
  int iVar2;
  int uVar3;
  
  if ((param_2 != 0) && (*(char *)(*(int *)(this + 0x58) + 0x213c) != '\0')) {
    // +0x58 = pointer to some game state or manager
    // +0x213c = flag indicating something is enabled
    iVar2 = FUN_0043b870(DAT_0112afb8);
    // DAT_0112afb8 likely a global pointer to PlayerInfo or similar
    if ((((*(uint *)(param_2 + 0x1f98) & 0x50c) != 0) &&
        // +0x1f98 = bitfield of flags, 0x50c = some action/state bits
        (((iVar2 != 0 && (*(int *)(iVar2 + 0x1c) != 0)) && (*(int *)(iVar2 + 0x1c) != 0x3c)))) &&
       // +0x1c = probably a timer or state value (0x3c = 60)
       (((*(byte *)(iVar2 + 0x3c) & 1) == 0 && (cVar1 = FUN_0071fa50(), cVar1 == '\0')))) {
      // +0x3c = byte flags, bit 0 = some condition
      uVar3 = FUN_0078b3a0();
      // Likely returns current mission/game phase or event type
      switch(uVar3) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 0xc:
      case 0xd:
        FUN_00894c90();
        // This function likely handles skill/stat increase or reputation change
        return;
      }
    }
  }
  return;
}