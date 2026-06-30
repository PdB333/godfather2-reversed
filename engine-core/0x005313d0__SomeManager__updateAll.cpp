// FUNC_NAME: SomeManager::updateAll
void SomeManager::updateAll(void)
{
  int iVar1;
  
  iVar1 = DAT_01194a68;
  if (DAT_01194a68 != 0) {
    do {
      // Call update on each item in the linked list
      FUN_005326c0(iVar1);
      iVar1 = *(int *)(iVar1 + 0x10);  // +0x10: next pointer in linked list
    } while (iVar1 != 0);
  }
  return;
}