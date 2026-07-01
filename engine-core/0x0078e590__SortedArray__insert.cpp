// FUNC_NAME: SortedArray::insert
void __thiscall SortedArray::insert(int this, int item)
{
  uint insertIndex = 0;
  
  if (*(uint *)(this + 0x14) != 0) { // +0x14: size (count of elements)
    int *listBase = *(int **)(this + 0x10); // +0x10: pointer to array of item pointers
    do {
      // Compare based on field at +0x170 in the item objects
      if (*(uint *)(*listBase + 0x170) < *(uint *)(item + 0x170)) break;
      insertIndex = insertIndex + 1;
      listBase = listBase + 1;
    } while (insertIndex < *(uint *)(this + 0x14));
  }
  
  // FUN_0078e500 is likely an array insertion/memmove (shifts elements to make room)
  int *slot = (int *)FUN_0078e500(insertIndex); // returns pointer to insertion position
  *slot = item;
  return;
}