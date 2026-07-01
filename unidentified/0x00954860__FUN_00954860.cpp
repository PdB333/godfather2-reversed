// FUNC_NAME: SomeClass::getSomeByteField
uint8_t __fastcall getSomeByteField(int thisPtr)
{
  // Returns byte at offset 0x50 from the object
  return *(uint8_t *)(thisPtr + 0x50);
}