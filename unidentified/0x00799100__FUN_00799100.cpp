// FUNC_NAME: SomeClass::getArrayElement
undefined4 __thiscall getArrayElement(int this, int index)
{
  // Accesses an array at offset +0x2a78 from 'this', each element is 4 bytes
  return *(undefined4 *)(this + 0x2a78 + index * 4);
}