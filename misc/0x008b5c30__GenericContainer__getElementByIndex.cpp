// FUNC_NAME: GenericContainer::getElementByIndex
undefined4 __thiscall GenericContainer::getElementByIndex(int this, uint index)
{
  undefined4 result;
  
  result = 0;
  if (index < *(uint *)(this + 0x108)) {
    // +0x108 = element count
    // +0x8 = start of element pointer array (each element 4 bytes)
    result = *(undefined4 *)(this + 8 + index * 4);
  }
  return result;
}