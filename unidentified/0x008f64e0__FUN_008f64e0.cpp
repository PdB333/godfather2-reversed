// FUNC_NAME: SomeClass::setCapacity
void __thiscall setCapacity(int this, uint newCapacity)
{
  // +0x4: current capacity (uint)
  if (*(uint *)(this + 4) < newCapacity) {
    FUN_008f6480(newCapacity); // likely reallocate internal buffer
    *(uint *)(this + 4) = newCapacity;
    return;
  }
  if (newCapacity < *(uint *)(this + 4)) {
    *(uint *)(this + 4) = newCapacity;
  }
  return;
}