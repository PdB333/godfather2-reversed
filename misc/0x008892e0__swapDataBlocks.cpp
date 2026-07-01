// FUNC_NAME: swapDataBlocks
void swapDataBlocks(undefined4 *block1, undefined4 *block2)
{
  int i;
  undefined4 temp[23]; // 0x5C bytes (23 * 4)
  undefined4 *srcPtr;
  undefined4 *dstPtr;

  // Copy block1 to temp
  srcPtr = block1;
  dstPtr = temp;
  for (i = 0x14; i != 0; i = i + -1) {
    *dstPtr = *srcPtr;
    srcPtr = srcPtr + 1;
    dstPtr = dstPtr + 1;
  }

  // Copy block2 to block1
  srcPtr = block2;
  for (i = 0x14; i != 0; i = i + -1) {
    *block1 = *srcPtr;
    srcPtr = srcPtr + 1;
    block1 = block1 + 1;
  }

  // Copy temp to block2
  srcPtr = temp;
  for (i = 0x14; i != 0; i = i + -1) {
    *block2 = *srcPtr;
    srcPtr = srcPtr + 1;
    block2 = block2 + 1;
  }
}