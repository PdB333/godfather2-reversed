// FUNC_NAME: GenericContainer::findByType
undefined4 __thiscall GenericContainer::findByType(int this, int typeId)
{
  uint index;
  undefined4 *entryPtr;
  
  index = 0;
  if (*(uint *)(this + 0xc) == 0) {
    return **(undefined4 **)(this + 8);
  }
  entryPtr = *(undefined4 **)(this + 8);
  do {
    if (**(int **)*entryPtr == typeId) {
      return *(undefined4 *)(*(int *)(this + 8) + index * 4);
    }
    index = index + 1;
    entryPtr = entryPtr + 1;
  } while (index < *(uint *)(this + 0xc));
  return **(undefined4 **)(this + 8);
}