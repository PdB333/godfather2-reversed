// FUNC_NAME: PlayerActionableInfo::getActionableTargetState
uint __thiscall PlayerActionableInfo::getActionableTargetState(int thisPtr, uint param_2)
{
  uint uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = *(int *)(thisPtr + 0xc4) + 1; // +0xC4: some counter/state
  if (uVar3 < param_2) {
    if ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x8e4) >> 8 & 1) == 0) { // +0x58: pointer to player data, +0x8E4: flags
      return CONCAT31((int3)(uVar3 >> 8),1); // return high byte of uVar3 with 1 in low byte
    }
  }
  else {
    iVar4 = FUN_007ab1e0(); // likely some game state check (e.g., isInCombat)
    if (((((iVar4 == 0) || ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x8e0) >> 10 & 1) == 0)) || // +0x8E0: another flags field
         (cVar2 = FUN_00701280(), cVar2 == '\0')) || // likely check if player is in vehicle
        (((*(uint *)(*(int *)(thisPtr + 0x58) + 0x8e4) >> 6 & 1) != 0 || // check bit 6 of flags
         (uVar3 = FUN_007aefe0(0x29), (char)uVar3 != '\0')))) && // check some condition with parameter 0x29
       (uVar1 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x8e4),
       uVar3 = CONCAT31((uint3)(ushort)(uVar1 >> 0x10),1), (uVar1 >> 8 & 1) == 0)) { // check bit 8 of flags
      return uVar3; // return high 16 bits of flags with 1 in low byte
    }
  }
  return uVar3 & 0xffffff00; // return uVar3 with low byte zeroed
}