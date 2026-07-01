// FUNC_NAME: copyStructArrayOf80Bytes
void copyStructArrayOf80Bytes(undefined4 *dest, int count, undefined4 *src)
{
  // Copies an array of structures, each 0x14 dwords (80 bytes), from src to dest.
  // count specifies the number of structures to copy.
  // dest and src are advanced by 0x14 dwords per iteration.
  if (count != 0) {
    do {
      if (dest != (undefined4 *)0x0) {
        undefined4 *srcPtr = src;
        undefined4 *destPtr = dest;
        for (int i = 0x14; i != 0; i = i + -1) {
          *destPtr = *srcPtr;
          srcPtr = srcPtr + 1;
          destPtr = destPtr + 1;
        }
      }
      count = count + -1;
      dest = dest + 0x14; // 0x14 dwords = 80 bytes per struct
    } while (count != 0);
  }
  return;
}