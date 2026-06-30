// FUNC_NAME: EntityManager::registerEntity
void __thiscall EntityManager::registerEntity(int thisPtr, int *entityPtr)
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  
  piVar5 = entityPtr;
  FUN_0046c6a0(entityPtr); // likely some entity validation or ref counting
  iVar1 = DAT_011298cc; // global EntityManager instance
  if (*piVar5 == DAT_0120e93c) { // check if entity type matches expected type
    iVar3 = *(int *)(DAT_011298cc + 0x20); // +0x20: capacity
    piVar5 = (int *)(DAT_011298cc + 0x18); // +0x18: entity array pointer
    if (*(int *)(DAT_011298cc + 0x1c) == iVar3) { // +0x1c: count == capacity
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = iVar3 * 2;
      }
      FUN_006e9220(iVar3); // resize entity array
    }
    iVar3 = *(int *)(iVar1 + 0x1c); // current count
    piVar5 = (int *)(*piVar5 + iVar3 * 4); // slot address
    *(int *)(iVar1 + 0x1c) = iVar3 + 1; // increment count
    if (piVar5 != (int *)0x0) {
      *piVar5 = thisPtr + -0x3c; // store offset-adjusted pointer (base - 0x3c)
    }
    if ((*(int *)(thisPtr + 0x28) == 0) || (*(int *)(thisPtr + 0x28) == 0x48)) { // check some state flags
      uVar4 = FUN_00445ff0(thisPtr + 0x18,0); // get some object from offset 0x18
      entityPtr = (int *)0x0;
      cVar2 = FUN_004480d0(uVar4,0xa7039c8,&entityPtr); // hash lookup or string compare
      FUN_006e9170(-(uint)(cVar2 != '\0') & (uint)entityPtr); // conditional callback
    }
    FUN_004086d0(&DAT_0120e93c); // release or decrement ref
  }
  return;
}