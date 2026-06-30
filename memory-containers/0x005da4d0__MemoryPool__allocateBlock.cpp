// FUNC_NAME: MemoryPool::allocateBlock
int* MemoryPool::allocateBlock(int* param_1, int param_2)
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int* in_EAX;
  
  iVar2 = *in_EAX;
  iVar3 = in_EAX[1];
  if (iVar2 == 0) {
    FUN_00b97aea(); // likely assertion/error handler
  }
  uVar1 = iVar3 + param_2 * 0x28; // 0x28 = 40 bytes per block
  if ((*(uint *)(iVar2 + 0xc) < uVar1) || (uVar1 < *(uint *)(iVar2 + 8))) {
    FUN_00b97aea(); // bounds check failed
  }
  param_1[1] = uVar1; // store offset
  *param_1 = iVar2;   // store pool pointer
  return param_1;
}