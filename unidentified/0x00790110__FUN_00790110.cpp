// FUNC_NAME: SomeClass::incrementDecrementRefCount
void __thiscall SomeClass::incrementDecrementRefCount(int this, char increment)
{
  if (increment != '\0') {
    *(int *)(this + 0x78) = *(int *)(this + 0x78) + 1; // +0x78: refCount
    return;
  }
  *(int *)(this + 0x78) = *(int *)(this + 0x78) + -1; // +0x78: refCount
  return;
}