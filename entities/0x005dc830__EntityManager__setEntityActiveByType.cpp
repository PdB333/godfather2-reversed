// FUNC_NAME: EntityManager::setEntityActiveByType
int EntityManager::setEntityActiveByType(int this, int entityType, char isActive)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (entityType != 0) {
    iVar1 = *(int *)(this + 8); // +0x8: entityList
    iVar2 = **(int **)(iVar1 + 0x1c); // +0x1c: linked list head
    while( true ) {
      iVar3 = *(int *)(*(int *)(this + 8) + 0x1c); // +0x1c: linked list head
      if ((iVar1 == 0) || (iVar1 != *(int *)(this + 8))) {
        FUN_00b97aea(); // likely assertion/error handler
      }
      if (iVar2 == iVar3) break;
      if (iVar1 == 0) {
        FUN_00b97aea(); // assertion
      }
      if (iVar2 == *(int *)(iVar1 + 0x1c)) {
        FUN_00b97aea(); // assertion
      }
      if (*(int *)(*(int *)(iVar2 + 0x10) + 0x2b4) == entityType) { // +0x10: entity data, +0x2b4: type field
        if (isActive == '\0') {
          if (iVar2 == *(int *)(iVar1 + 0x1c)) {
            FUN_00b97aea(); // assertion
          }
          *(undefined1 *)(*(int *)(iVar2 + 0x10) + 0x298) = 0; // +0x298: active flag
        }
        else {
          if (iVar2 == *(int *)(iVar1 + 0x1c)) {
            FUN_00b97aea(); // assertion
          }
          *(undefined1 *)(*(int *)(iVar2 + 0x10) + 0x298) = 1; // +0x298: active flag
        }
      }
      FUN_005e09e0(); // likely iterator advance
    }
    return 1;
  }
  return 0;
}