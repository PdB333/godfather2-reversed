// FUNC_NAME: getBitCountForValue
int __fastcall getBitCountForValue(int param_1, int *param_2)
{
  int value;
  int bitCount;
  uint mask;
  
  value = *param_2;
  if (value != 0) {
    bitCount = value * 0x1c + -0x1c;
    for (mask = *(uint *)(param_2[3] + -4 + value * 4); mask != 0; mask = mask >> 1) {
      bitCount = bitCount + 1;
    }
    return bitCount;
  }
  return 0;
}