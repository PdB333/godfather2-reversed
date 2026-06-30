// FUNC_NAME: BigInt::shiftLeft
int BigInt::shiftLeft(int *dst, int *src)
{
  uint carry;
  int result;
  uint temp;
  uint *srcData;
  uint *dstData;
  int i;
  undefined4 *zeroPtr;
  
  if ((*src + 1 <= src[1]) || (result = FUN_00667740(), result == 0)) {
    // Perform left shift by 1 bit on the big integer
    result = *dst;
    *dst = *src;
    srcData = (uint *)src[3];  // +0xC: data pointer
    dstData = (uint *)dst[3];  // +0xC: data pointer
    carry = 0;
    i = 0;
    if (0 < *src) {
      do {
        temp = *srcData;
        *dstData = temp * 2 & 0xfffffff | carry;  // 28-bit shift with carry
        carry = temp >> 0x1b;  // Extract high 5 bits as new carry
        i = i + 1;
        dstData = dstData + 1;
        srcData = srcData + 1;
      } while (i < *src);
      if (carry != 0) {
        *dstData = 1;  // Extend with overflow digit
        *dst = *dst + 1;  // Increment digit count
      }
    }
    // Zero out remaining digits if destination was larger
    i = *dst;
    if (i < result) {
      zeroPtr = (undefined4 *)(dst[3] + i * 4);
      for (result = result - i; result != 0; result = result + -1) {
        *zeroPtr = 0;
        zeroPtr = zeroPtr + 1;
      }
    }
    dst[2] = src[2];  // +0x8: sign/negative flag
    result = 0;
  }
  return result;
}