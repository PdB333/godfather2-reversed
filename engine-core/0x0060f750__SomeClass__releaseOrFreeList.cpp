// FUNC_NAME: SomeClass::releaseOrFreeList
void SomeClass::releaseOrFreeList(int *param_1)
{
  int iVar1;
  
  iVar1 = param_1[1]; // +0x04: count or remaining items
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    FUN_00609aa0(); // likely releaseItem or freeNode
  }
  if (*param_1 != 0) { // +0x00: pointer to allocated block
    FUN_009c8f10(*param_1); // likely operator delete or free
  }
  return;
}