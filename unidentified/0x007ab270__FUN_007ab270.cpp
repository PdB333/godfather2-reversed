// FUNC_NAME: SomeClass::getSomeValue
undefined4 __fastcall SomeClass::getSomeValue(int this)
{
  // Dereferences pointer at this+0x58, then accesses offset 0x24f4 from that pointer
  // +0x58: pointer to some sub-object or manager
  // +0x24f4: offset within that sub-object where the value is stored
  return *(undefined4 *)(*(int *)(this + 0x58) + 0x24f4);
}