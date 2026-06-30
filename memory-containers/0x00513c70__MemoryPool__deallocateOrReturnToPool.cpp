// FUNC_NAME: MemoryPool::deallocateOrReturnToPool
int* MemoryPool::deallocateOrReturnToPool(int* result)
{
  int* piVar1;
  int iVar2;
  int* in_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  int unaff_FS_OFFSET;
  
  if (in_EAX[5] != -1) {
    // Not a special block (allocated from pool)
    piVar1 = *(int **)(unaff_FS_OFFSET + 0x2c);
    iVar4 = 0;
    if (*in_EAX != 0) {
      iVar4 = *(int *)(*piVar1 + 8) + *in_EAX;
    }
    // Calculate block index based on pool size (0x2a0 = 672 bytes)
    iVar4 = in_EAX[5] * 0x2a0 + iVar4;
    if (iVar4 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = iVar4 - *(int *)(*piVar1 + 8);
    }
    iVar3 = *piVar1;
    iVar2 = *(int *)(iVar5 + *(int *)(iVar3 + 8));
    // Decrement reference count
    in_EAX[6] = in_EAX[6] + -1;
    // Set next free block index
    in_EAX[5] = iVar2;
    if ((uint)in_EAX[6] < (uint)in_EAX[7]) {
      in_EAX[7] = in_EAX[6];
    }
    // Clear the block's data if it exists (8 * 0x50 = 0x280 bytes)
    if ((iVar5 != 0) && (iVar3 = *(int *)(iVar3 + 8) + iVar5, iVar3 != 0)) {
      *(undefined4 *)(iVar3 + 0x50) = 0;
      *(undefined4 *)(iVar3 + 0xa0) = 0;
      *(undefined4 *)(iVar3 + 0xf0) = 0;
      *(undefined4 *)(iVar3 + 0x140) = 0;
      *(undefined4 *)(iVar3 + 400) = 0;
      *(undefined4 *)(iVar3 + 0x1e0) = 0;
      *(undefined4 *)(iVar3 + 0x230) = 0;
      *(undefined4 *)(iVar3 + 0x280) = 0;
    }
    // Set result: whether block was found and its offset
    result[1] = (uint)(iVar4 != 0);
    *result = iVar5;
    return result;
  }
  // Special block (allocated separately), call its destructor
  if ((int *)in_EAX[8] != (int *)0x0) {
    (**(code **)(*(int *)in_EAX[8] + 4))(result);
    return result;
  }
  // Null block
  *result = 0;
  result[1] = 0;
  return result;
}