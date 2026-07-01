// FUNC_NAME: SomeContainer::removeByKey
int __thiscall SomeContainer::removeByKey(int this, int *key)
{
  uint count = *(uint *)(this + 0xc); // +0x0C: count of elements
  uint index = 0;
  
  if (count != 0) {
    int *array = *(int **)(this + 8); // +0x08: pointer to array of pointers
    do {
      int element = *array;
      // Compare 4 ints at offsets +0x1C, +0x20, +0x24, +0x28 as the key
      if ((((*(int *)(element + 0x1c) == *key) && 
            (*(int *)(element + 0x20) == key[1])) &&
           (*(int *)(element + 0x24) == key[2])) && 
          (*(int *)(element + 0x28) == key[3])) {
        // Found match, remove by shifting elements left
        if (index < count - 1) {
          do {
            *(int *)(*(int *)(this + 8) + index * 4) =
                 *(int *)(*(int *)(this + 8) + 4 + index * 4);
            index = index + 1;
          } while (index < *(int *)(this + 0xc) - 1U);
        }
        *(int *)(this + 0xc) = *(int *)(this + 0xc) - 1;
        return element;
      }
      index = index + 1;
      array = array + 1;
    } while (index < count);
  }
  return 0;
}