// FUNC_NAME: StreamManager::updateStreaming
void StreamManager::updateStreaming(void)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int this;
  undefined1 local_10 [12];
  
  FUN_004086d0(&DAT_012069d4);
  if (*(int *)(this + 0x18) != 0) {
    FUN_0043e500(*(int *)(this + 0x18));
    iVar1 = *(int *)(this + 0x18);
    if ((*(char *)(iVar1 + 4) != '\0') && (*(int *)(iVar1 + 0x290) != 0)) {
      FUN_005ddd90(DAT_01223508,*(int *)(iVar1 + 0x290));
      *(undefined1 *)(iVar1 + 4) = 0;
    }
    *(undefined4 *)(this + 0x18) = 0;
  }
  if (*(int *)(this + 0x10) != 0) {
    iVar1 = *(int *)(*(int *)(this + 0x10) + 0x20);
    while (iVar1 != 0) {
      iVar1 = *(int *)(this + 0x10);
      piVar2 = *(int **)(iVar1 + 0x1c);
      piVar3 = (int *)*piVar2;
      if (piVar3 == piVar2) {
        FUN_00b97aea();
      }
      iVar4 = piVar3[4];
      FUN_004c9bf0(*(undefined4 *)(this + 0x10),local_10,iVar1,piVar3);
      if (iVar4 != 0) {
        FUN_009c8eb0(iVar4);
      }
      iVar1 = *(int *)(*(int *)(this + 0x10) + 0x20);
    }
  }
  if (DAT_012234bc != 0) {
    FUN_005e48d0();
  }
  iVar1 = DAT_0122350c;
  if ((DAT_0122350c != 0) && (*(int *)(DAT_0122350c + 0x173c) != 0)) {
    iVar4 = *(int *)(DAT_0122350c + 0x173c);
    if (iVar4 != 1) {
      puVar5 = *(undefined4 **)(DAT_0122350c + 0x1738);
      *puVar5 = puVar5[iVar4 * 2 + -2];
      puVar5[1] = puVar5[iVar4 * 2 + -1];
    }
    *(int *)(iVar1 + 0x173c) = *(int *)(iVar1 + 0x173c) + -1;
  }
  return;
}