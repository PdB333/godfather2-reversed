// FUNC_NAME: PlayerActionableInfo::findActionableByTargetId
int __thiscall PlayerActionableInfo::findActionableByTargetId(int *this, int targetId)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (targetId != 0) {
    iVar1 = FUN_008fdfd0(); // likely some global manager or system check
    if (iVar1 != 0) {
      iVar2 = FUN_00791540(); // likely getTargetId or similar
      iVar1 = 1;
      iVar3 = (**(code **)(*this + 0x70))(); // virtual call: getActionableCount()
      if (1 < iVar3) {
        do {
          iVar3 = FUN_008c74d0(*(undefined4 *)(this[0x15] + iVar1 * 4)); // getActionableId at index iVar1
          if (iVar3 == iVar2) {
            return iVar1;
          }
          iVar1 = iVar1 + 1;
          iVar3 = (**(code **)(*this + 0x70))(); // virtual call: getActionableCount()
        } while (iVar1 < iVar3);
      }
      return -1;
    }
  }
  return -1;
}