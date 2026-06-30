// FUNC_NAME: SomeClass::getSomeValue
int SomeClass::getSomeValue(void)
{
  // Check if bit 0x20 of byte at offset +0xB is set and value at offset +0x0 is > 1
  if (((*(byte *)(this + 0xB) & 0x20) != 0) && (1 < *(int *)this)) {
    // Return value at offset +0x1C (in_EAX[7] = this + 0x1C)
    return *(int *)(this + 0x1C);
  }
  // Return value at offset +0x14 (in_EAX[5] = this + 0x14)
  return *(int *)(this + 0x14);
}