// FUNC_NAME: SomeContainer::removeByKey
int __thiscall SomeContainer::removeByKey(int this, int *key)
{
  uint count;
  int result;
  uint i;
  int *ptr;
  
  count = *(uint *)(this + 0xc);
  i = 0;
  if (count != 0) {
    ptr = *(int **)(this + 8);
    do {
      result = *ptr;
      // Compare 4 ints at offsets 0x1c, 0x20, 0x24, 0x28 with the key array
      if ((((*(int *)(result + 0x1c) == *key) && (*(int *)(result + 0x20) == key[1])) &&
          (*(int *)(result + 0x24) == key[2])) && (*(int *)(result + 0x28) == key[3])) {
        // Found match, shift remaining elements left
        if (i < count - 1) {
          do {
            *(int *)(*(int *)(this + 8) + i * 4) =
                 *(int *)(*(int *)(this + 8) + 4 + i * 4);
            i = i + 1;
          } while (i < *(int *)(this + 0xc) - 1U);
        }
        *(int *)(this + 0xc) = *(int *)(this + 0xc) + -1;
        return result;
      }
      i = i + 1;
      ptr = ptr + 1;
    } while (i < count);
  }
  return 0;
}