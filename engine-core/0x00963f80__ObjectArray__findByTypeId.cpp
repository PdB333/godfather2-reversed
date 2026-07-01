// FUNC_NAME: ObjectArray::findByTypeId
int * __thiscall ObjectArray::findByTypeId(int thisPtr, int typeId)
{
  uint index = 0;
  int *result = (int *)0x0;
  
  if (*(uint *)(thisPtr + 8) != 0) {
    int *arrayBase = *(int **)(thisPtr + 4);
    while (true) {
      result = (int *)*arrayBase;
      if (result != (int *)0x0 && *result != 0 && *(int *)(*result + 0x70) == typeId) {
        break;
      }
      index = index + 1;
      arrayBase = arrayBase + 1;
      if (*(uint *)(thisPtr + 8) <= index) {
        return (int *)0x0;
      }
    }
  }
  return result;
}