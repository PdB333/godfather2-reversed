// FUNC_NAME: Player::isValidTarget
char __thiscall Player::isValidTarget(void *this, int *pTarget, char *outBlocked)
{
  uint uVar1;
  char isAlly;
  char cVar3;
  int basePtr;
  uint count;
  int *ppHandle;
  
  // Determine the base object (family component or follow target)
  if (*(int *)((char *)this + 0x2138) == 0) {
    if (*(int *)((char *)this + 0x1ed8) == 0) {
      basePtr = 0;
    }
    else {
      basePtr = *(int *)((char *)this + 0x1ed8) + -0x48;
    }
  }
  else {
    basePtr = FUN_008c74d0(*(int *)((char *)this + 0x2138));
  }
  
  // Check if pTarget has a specific relationship with base object's faction ID (+0x88)
  isAlly = FUN_0043c6c0(pTarget, *(undefined4 *)(basePtr + 0x88));
  
  // Count of handles in the block list (offset +0x64 from base)
  count = *(uint *)(basePtr + 100);
  if (count != 0) {
    ppHandle = (int *)(basePtr + 0x58);
    do {
      if ((isAlly == '\0') && (*ppHandle != 0)) {
        int handlePtr = FUN_008c74d0(*ppHandle);
        if (handlePtr != 0) {
          cVar3 = FUN_0043c6c0(pTarget, *(undefined4 *)(handlePtr + 0x88));
          if (cVar3 != '\0') {
            *outBlocked = 1;
            return '\x01';
          }
        }
      }
      count = count - 1;
      ppHandle = ppHandle + 1;
    } while (count != 0);
  }
  
  if (isAlly == '\0') {
    cVar3 = FUN_0043c6c0(pTarget, 4);
    if ((cVar3 != '\0') && (pTarget != (int *)0x0)) {
      int owner = (**(code **)(*pTarget + 0x1e8))();
      if (owner == 0) {
        if ((pTarget[0x2e4] == *(int *)((char *)this + 0x1ed4)) ||
           ((*(int *)((char *)this + 0x1ed4) == 0x637b907 && (((uint)pTarget[0x322] >> 9 & 1) != 0)))) {
          isAlly = '\x01';
        }
      }
      else {
        owner = (**(code **)(*pTarget + 0x1e8))();
        if ((owner != 0) && (*(int *)((char *)owner + 0x1ed4) == *(int *)((char *)this + 0x1ed4))) {
          return '\x01';
        }
      }
    }
  }
  return isAlly;
}