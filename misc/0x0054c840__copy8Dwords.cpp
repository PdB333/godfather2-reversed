// FUNC_NAME: copy8Dwords
void __thiscall copy8Dwords(undefined4 *dst, undefined4 *src)
{
  *dst = *src;
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = src[3];
  dst[4] = src[4];
  dst[5] = src[5];
  dst[6] = src[6];
  dst[7] = src[7];
  return;
}