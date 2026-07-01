// FUNC_NAME: ObjectPool::clear
void __fastcall ObjectPool::clear(int *thisPool)
{
  int iVar1;
  
  iVar1 = thisPool[1]; // +0x04: count of allocated slots
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    if (*(int *)(*thisPool + iVar1 * 8) != 0) { // +0x00: pointer to pool array (each slot 8 bytes)
      FUN_004daf90(*thisPool + iVar1 * 8); // likely ObjectPool::destroySlot or similar
    }
  }
  thisPool[1] = 0; // reset count
  FUN_009c8f10(*thisPool); // likely operator delete[] or free
  *thisPool = 0; // +0x00: pool array pointer
  thisPool[2] = 0; // +0x08: some capacity or other field
  return;
}