// FUNC_NAME: SomeClass::findObjectByTypeAndId
int __thiscall SomeClass::findObjectByTypeAndId(int this, int *typeAndId)
{
  int result;
  int *objectPtr;
  uint index;
  
  result = 0;
  index = 0;
  if (*(uint *)(this + 0x17c) != 0) {
    objectPtr = *(int **)(this + 0x178);
    while ((*(int *)(*objectPtr + 0x100) != *typeAndId || (*(int *)(*objectPtr + 0xfc) != typeAndId[1]))) {
      index = index + 1;
      objectPtr = objectPtr + 1;
      if (*(uint *)(this + 0x17c) <= index) {
        return 0;
      }
    }
    result = (*(int **)(this + 0x178))[index];
  }
  return result;
}