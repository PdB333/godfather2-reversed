// FUNC_NAME: SomeClass::getArrayElement
undefined4 __thiscall getArrayElement(int this, int index)
{
  // Returns element from an array stored at offset +0x14 in the object.
  // Each element is 4 bytes (likely a pointer or int).
  return *(undefined4 *)(this + 0x14 + index * 4);
}