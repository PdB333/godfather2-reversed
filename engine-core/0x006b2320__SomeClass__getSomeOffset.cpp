// FUNC_NAME: SomeClass::getSomeOffset
int __fastcall SomeClass::getSomeOffset(int param_1)
{
  // Returns (value at +0xA0 + value at +0x88) * 0x14 + 0x60
  // Likely computing an offset into an array or structure based on two fields
  return (*(int *)(param_1 + 0xa0) + *(int *)(param_1 + 0x88)) * 0x14 + 0x60;
}