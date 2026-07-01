// FUNC_NAME: SomeClass::serializeData
int __thiscall serializeData(int thisPtr, undefined4 *outBuffer)
{
  int count;
  undefined4 *dst;
  uint i;
  
  outBuffer[0] = 0;
  outBuffer[1] = 0;
  outBuffer[2] = 0;
  outBuffer[3] = 0;
  outBuffer[4] = 0;
  outBuffer[5] = 0;
  outBuffer[6] = 0;
  outBuffer[7] = 0;
  outBuffer[8] = *(undefined4 *)(thisPtr + 0x40); // +0x40: firstCount
  outBuffer[9] = 0;
  outBuffer[10] = 0;
  outBuffer[0xb] = 0;
  i = 0;
  dst = outBuffer + 0xc;
  if (*(int *)(thisPtr + 0x40) != 0) {
    do {
      count = i * 4;
      i = i + 1;
      *dst = *(undefined4 *)(thisPtr + 0x14 + count); // +0x14: firstArray
      dst = dst + 1;
    } while (i < *(uint *)(thisPtr + 0x40));
  }
  *dst = *(undefined4 *)(thisPtr + 0x70); // +0x70: secondCount
  dst[1] = 0;
  dst[2] = 0;
  dst[3] = 0;
  dst = dst + 4;
  i = 0;
  if (*(int *)(thisPtr + 0x70) != 0) {
    do {
      count = i * 4;
      i = i + 1;
      *dst = *(undefined4 *)(thisPtr + 0x44 + count); // +0x44: secondArray
      dst = dst + 1;
    } while (i < *(uint *)(thisPtr + 0x70));
  }
  *dst = *(undefined4 *)(thisPtr + 0xa0); // +0xa0: thirdCount
  dst[1] = 0;
  dst[2] = 0;
  dst[3] = 0;
  dst = dst + 4;
  i = 0;
  if (*(int *)(thisPtr + 0xa0) != 0) {
    do {
      count = i * 4;
      i = i + 1;
      *dst = *(undefined4 *)(thisPtr + 0x74 + count); // +0x74: thirdArray
      dst = dst + 1;
    } while (i < *(uint *)(thisPtr + 0xa0));
  }
  *dst = *(undefined4 *)(thisPtr + 0xd0); // +0xd0: fourthCount
  dst[1] = 0;
  dst[2] = 0;
  dst[3] = 0;
  dst = dst + 4;
  i = 0;
  if (*(int *)(thisPtr + 0xd0) != 0) {
    do {
      count = i * 4;
      i = i + 1;
      *dst = *(undefined4 *)(thisPtr + 0xa4 + count); // +0xa4: fourthArray
      dst = dst + 1;
    } while (i < *(uint *)(thisPtr + 0xd0));
  }
  return (int)dst - (int)outBuffer;
}