// FUNC_NAME: SomeClass::findByEntityId
int SomeClass::findByEntityId(int entityId)
{
  uint index = 0;
  if (*(uint *)(this + 0x18) != 0) {
    int *ptr = (int *)(*(int *)(this + 0x14) + 4);
    while (*(int *)(*ptr + 0x28) != entityId) {
      index = index + 1;
      ptr = ptr + 3;
      if (*(uint *)(this + 0x18) <= index) {
        return 0;
      }
    }
    if (-1 < (int)index) {
      return *(int *)(*(int *)(this + 4) + index * 4);
    }
  }
  return 0;
}