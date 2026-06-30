// FUNC_NAME: EntityPointerArray::resetOrClear
void EntityPointerArray::resetOrClear(int *array)
{
  int iVar1;
  int count;
  int index;
  
  count = array[1]; // +0x04: current element count
  if (count != 0) {
    while (index = count + -1, -1 < index) {
      iVar1 = *array; // +0x00: pointer to data array
      int *entityPtr = *(int **)(iVar1 + 4 + index * 8); // +0x04: element at index
      if (entityPtr != 0) {
        *(short *)(entityPtr + 8) = *(short *)(entityPtr + 8) + -1; // +0x08: reference count decrement
        if (*(short *)(entityPtr + 8) == 0) {
          FUN_00616dc0(entityPtr); // release/destroy entity
          (**(code **)(*DAT_01205964 + 4))(entityPtr,0); // delete via vtable
        }
        *(undefined4 *)(iVar1 + 4 + index * 8) = 0; // clear pointer
      }
    }
    array[1] = 0; // reset count to zero
  }
  return;
}