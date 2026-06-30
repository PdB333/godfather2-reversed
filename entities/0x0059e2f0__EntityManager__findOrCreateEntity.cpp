// FUNC_NAME: EntityManager::findOrCreateEntity
int EntityManager::findOrCreateEntity(void)
{
  int in_EAX;
  int iVar1;
  
  if (DAT_0119a9cc == 0) {
    return 0;
  }
  iVar1 = **(int **)(DAT_0119a9cc + 0x2514); // +0x2514: entity list head pointer
  while( true ) {
    if (iVar1 == 0) {
      iVar1 = (*DAT_0119caf0)(0x70,0x10); // allocate 0x70 bytes, alignment 0x10
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = FUN_0059c700(0); // Entity constructor
      }
      FUN_005b22e0(); // register entity in manager
      return iVar1;
    }
    if (*(int *)(iVar1 + 0x30) == in_EAX) break; // +0x30: entity ID field
    iVar1 = *(int *)(iVar1 + 0x60); // +0x60: next entity pointer
  }
  return iVar1;
}