// FUNC_NAME: SomeClass::getSomeBufferSize
int __fastcall SomeClass::getSomeBufferSize(int this)
{
  // Returns the size of some buffer/array stored at offset 0x20 in this object,
  // adding 4 to account for a header or length prefix.
  // +0x20: pointer to buffer metadata (e.g., a struct with count + data)
  return *(int *)(this + 0x20) + 4;
}