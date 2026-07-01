// FUNC_NAME: Array::mergeSortRange
void Array::mergeSortRange(undefined4 *array, undefined4 *start, undefined4 *end, undefined4 param_4)
{
  int iVar1;
  undefined4 *srcPtr;
  undefined4 *dstPtr;
  undefined4 *current;
  undefined4 tempBuffer [23];
  
  FUN_00889320(array,start,param_4);
  current = start;
  if (start < end) {
    do {
      if ((uint)current[2] < (uint)array[2]) {
        srcPtr = current;
        dstPtr = tempBuffer;
        for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
          *dstPtr = *srcPtr;
          srcPtr = srcPtr + 1;
          dstPtr = dstPtr + 1;
        }
        srcPtr = array;
        dstPtr = current;
        for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
          *dstPtr = *srcPtr;
          srcPtr = srcPtr + 1;
          dstPtr = dstPtr + 1;
        }
        FUN_00888890(array,0,((int)start - (int)array) / 0x50,0,tempBuffer,param_4);
      }
      current = current + 0x14;
    } while (current < end);
  }
  FUN_008893a0(array,start,param_4);
  return;
}