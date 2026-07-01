// FUNC_NAME: PlayerActionableInfo::resetActionableInfo
void __thiscall PlayerActionableInfo::resetActionableInfo(int this, char param_2)
{
  int iVar1;
  
  iVar1 = FUN_0083c160(); // likely getMaxActionableTargets() or similar
  iVar1 = iVar1 + -1;
  if (0 < iVar1) {
    if (param_2 != '\0') {
      iVar1 = 1;
    }
    FUN_0083e1b0(iVar1); // likely clearActionableTarget or setActionableTargetCount
  }
  *(undefined4 *)(this + 0xa0) = 0; // +0xA0: currentActionableTargetIndex or similar
  return;
}