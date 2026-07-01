// FUNC_NAME: SomeClass::copySomeData
void __thiscall copySomeData(int this, int other)
{
  // Copy two 4-byte values from source object to destination object
  // +0x174 and +0x170 are likely fields in the class
  *(undefined4 *)(this + 0x174) = *(undefined4 *)(other + 0x10);
  *(undefined4 *)(this + 0x170) = *(undefined4 *)(other + 0x14);
  return;
}