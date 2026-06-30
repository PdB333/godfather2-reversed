// FUNC_NAME: SomeClass::getIndexFromOffset
int __fastcall getIndexFromOffset(int *param_1)
{
  int in_EAX; // eax register, likely an offset value
  
  // param_1[2] is some base index or offset
  // *param_1 points to a structure with a field at +0x20 (likely an array start offset)
  // (in_EAX - *(int *)(*param_1 + 0x20)) calculates the difference from the array start
  // Dividing by 0x24 (36) gives the element index (each element is 0x24 bytes)
  // Multiplying by 0xc (12) converts to a different stride (likely a different array with 12-byte elements)
  return param_1[2] + ((in_EAX - *(int *)(*param_1 + 0x20)) / 0x24) * 0xc;
}