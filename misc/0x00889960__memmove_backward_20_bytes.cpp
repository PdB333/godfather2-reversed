// FUNC_NAME: memmove_backward_20_bytes
void memmove_backward_20_bytes(undefined4 *dest, undefined4 *src, undefined4 *end)
{
  int iVar1;
  undefined4 *pSrc;
  undefined4 *pDst;
  
  if (src != dest) {
    do {
      src = src + -0x14;
      end = end + -0x14;
      pSrc = src;
      pDst = end;
      for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pDst = *pSrc;
        pSrc = pSrc + 1;
        pDst = pDst + 1;
      }
    } while (src != dest);
  }
  return;
}