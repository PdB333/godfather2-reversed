// FUNC_NAME: MemoryManager::zeroAndCopyString
void MemoryManager::zeroAndCopyString(void *this, undefined4 *param_2)
{
  undefined4 *puVar1;
  undefined2 *puVar2;
  
  puVar1 = (undefined4 *)MemoryManager::allocate(this, &this);  // FUN_0098cd30
  if (puVar1 != param_2) {
    puVar2 = (undefined2 *)*param_2;
    if (puVar2 == (undefined2 *)0x0) {
      puVar2 = &DAT_00e2df14;  // Default empty string
    }
    FUN_004dbb10(puVar2,0,param_2[1]);  // memcpy/copy function
  }
  return;
}