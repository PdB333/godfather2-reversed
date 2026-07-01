// FUNC_NAME: SomeClass::findIndexById
uint __thiscall SomeClass::findIndexById(int this, int id)
{
  uint index;
  int *idArray;
  
  index = 0xffffffff;
  if (*(uint *)(this + 0x54) != 0) {
    idArray = (int *)(this + 0x34);
    index = 0;
    while (*idArray != id) {
      index = index + 1;
      idArray = idArray + 1;
      if (*(uint *)(this + 0x54) <= index) {
        return 0xffffffff;
      }
    }
  }
  return index;
}