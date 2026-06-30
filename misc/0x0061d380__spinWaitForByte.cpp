// FUNC_NAME: spinWaitForByte
void __fastcall spinWaitForByte(uint byteVal)
{
  for (byteVal = byteVal & 0xff; byteVal != 0; byteVal = byteVal - 1) {
  }
  return;
}