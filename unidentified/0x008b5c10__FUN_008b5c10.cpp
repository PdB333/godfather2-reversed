// FUNC_NAME: SomeClass::getSomeBufferSize
int __fastcall SomeClass::getSomeBufferSize(int this)
{
  // +0x108: some count or offset
  // +0x10c: another count or offset
  // Returns (value1 + value2) * 4 + 12
  return (*(int *)(this + 0x10c) + *(int *)(this + 0x108)) * 4 + 0xc;
}