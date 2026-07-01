// FUNC_NAME: EntityManager::countTotalEntities
int __fastcall EntityManager::countTotalEntities(int this)
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 totalCount;
  
  iVar1 = **(int **)(this + 0x30); // +0x30: first entity list head pointer
  totalCount = 0;
  while( true ) {
    iVar3 = *(int *)(this + 0x30); // +0x30: entity list head
    if (this == -0x2c) {
      FUN_00b97aea(); // likely debug assertion or iterator validation
    }
    if (iVar1 == iVar3) break;
    if (this == -0x2c) {
      FUN_00b97aea();
    }
    if (iVar1 == *(int *)(this + 0x30)) {
      FUN_00b97aea();
    }
    iVar3 = 0;
    for (puVar2 = *(undefined4 **)(iVar1 + 0x10); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      iVar3 = iVar3 + 1;
    }
    totalCount = totalCount + iVar3;
    FUN_008ea280(); // likely iterator advance
  }
  iVar1 = **(int **)(this + 0x24); // +0x24: second entity list head pointer
  while( true ) {
    iVar3 = *(int *)(this + 0x24); // +0x24: second entity list head
    if (this == -0x20) {
      FUN_00b97aea();
    }
    if (iVar1 == iVar3) break;
    if (this == -0x20) {
      FUN_00b97aea();
    }
    if (iVar1 == *(int *)(this + 0x24)) {
      FUN_00b97aea();
    }
    iVar3 = 0;
    for (puVar2 = *(undefined4 **)(iVar1 + 0x10); puVar2 != (undefined4 *)0x0;
        puVar2 = (undefined4 *)*puVar2) {
      iVar3 = iVar3 + 1;
    }
    totalCount = totalCount + iVar3;
    FUN_008ea280();
  }
  return totalCount;
}