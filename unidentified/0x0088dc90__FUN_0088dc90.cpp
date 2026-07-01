// FUNC_NAME: SomeClass::addToArray
void __thiscall addToArray(int this, undefined4 value)
{
  // +0x148: current count of elements in the array
  // +0x80: start of the array (each element is 4 bytes)
  if (*(uint *)(this + 0x148) < 0x32) { // max 50 elements (0x32)
    *(undefined4 *)(this + 0x80 + *(uint *)(this + 0x148) * 4) = value;
    *(int *)(this + 0x148) = *(int *)(this + 0x148) + 1;
  }
  return;
}