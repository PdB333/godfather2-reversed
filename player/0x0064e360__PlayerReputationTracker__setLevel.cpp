//FUNC_NAME: PlayerReputationTracker::setLevel
uint __thiscall PlayerReputationTracker::setLevel(int *this, int newLevel)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  
  // Clamp or convert newLevel (0x20 = 32, maybe bit count or max)
  FUN_0064b9e0(0x20, &newLevel);
  
  // Get virtual function at vtable+0x50 (likely getLevelCount or getMaxLevel)
  pcVar2 = *(code **)(*this + 0x50);
  this[0x7c] = newLevel; // +0x1F0: currentLevel
  uVar5 = (*pcVar2)();    // returns maxLevel or levelCount
  
  uVar3 = this[0x7c];    // currentLevel
  if (uVar3 <= *(uint *)(&DAT_01223170 + uVar5 * 0x24)) {
    // Level is within valid range
    iVar6 = (**(code **)(*this + 0x50))(); // call again? maybe getLevelCount again
    uVar5 = iVar6 * 0x24;
    if ((uVar3 == *(uint *)(&DAT_01223170 + uVar5)) ||
       ((uVar3 != 0 &&
        (piVar1 = (int *)(&DAT_01223178 + uVar5), uVar5 = *(uint *)(*piVar1 + uVar3 * 4),
        *(int *)(uVar5 + 8) != *(int *)(*(int *)(*piVar1 + -4 + uVar3 * 4) + 8))))) {
      // Level is valid; compute exponent or flag
      uVar3 = this[0x7c];
      fVar4 = (float)(int)uVar3;
      if ((int)uVar3 < 0) {
        fVar4 = fVar4 + DAT_00e44578; // 0x4F000000? likely a float constant for negative conversion
      }
      iVar6 = (((uVar3 - 1 & uVar3) != 0) - 0x7f) + ((uint)fVar4 >> 0x17);
      this[0x7d] = iVar6; // +0x1F4: some computed value (maybe exponent or bitmask)
      return CONCAT31((int3)((uint)iVar6 >> 8),1); // return success with flag
    }
  }
  return uVar5 & 0xffffff00; // return error or invalid
}