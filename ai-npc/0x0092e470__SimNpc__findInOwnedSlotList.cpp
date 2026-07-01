// FUNC_NAME: SimNpc::findInOwnedSlotList
int SimNpc::findInOwnedSlotList(void)
{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  
  iVar2 = DAT_0112ebb4;
  puVar1 = (undefined4 *)(DAT_0112ebb4 + 0xf0);
  if ((*(int *)(DAT_0112ebb4 + 0xf4) != 0) &&
     ((*(char *)(DAT_0112ebb4 + 0x124) == '\0' || (cVar3 = FUN_0089c630(), cVar3 == '\0')))) {
    if (**(int **)(DAT_012233a0 + 4) == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
    }
    if ((*(int *)(DAT_0112ebb4 + 0x16c) != 0) && (iVar4 != 0)) {
      iVar4 = FUN_004baf60(*(undefined4 *)(iVar4 + 0x1ef8));
      uVar6 = 0;
      if (*(uint *)(iVar2 + 0xf4) != 0) {
        piVar5 = (int *)*puVar1;
        do {
          if (*piVar5 == *(int *)(iVar4 + 8)) {
            if ((int)uVar6 < 0) {
              return -1;
            }
            return uVar6 + 1;
          }
          uVar6 = uVar6 + 1;
          piVar5 = piVar5 + 1;
        } while (uVar6 < *(uint *)(iVar2 + 0xf4));
        return -1;
      }
    }
  }
  return -1;
}