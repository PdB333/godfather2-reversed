// FUNC_NAME: ObjectPool::removeByKey
int __thiscall ObjectPool::removeByKey(int this, int *key)
{
  uint count;
  int result;
  uint i;
  int *poolPtr;
  
  count = *(uint *)(this + 0xc); // +0x0C: count of objects in pool
  i = 0;
  if (count != 0) {
    poolPtr = *(int **)(this + 8); // +0x08: pointer to pool array
    do {
      result = *poolPtr;
      // Compare 4 ints at offsets 0x1C, 0x20, 0x24, 0x28 as the key
      if ((((*(int *)(result + 0x1c) == *key) && 
            (*(int *)(result + 0x20) == key[1])) &&
           (*(int *)(result + 0x24) == key[2])) && 
          (*(int *)(result + 0x28) == key[3])) {
        // Found matching object, remove it by shifting remaining elements left
        if (i < count - 1) {
          do {
            *(undefined4 *)(*(int *)(this + 8) + i * 4) =
                 *(undefined4 *)(*(int *)(this + 8) + 4 + i * 4);
            i = i + 1;
          } while (i < *(int *)(this + 0xc) - 1U);
        }
        *(int *)(this + 0xc) = *(int *)(this + 0xc) + -1; // Decrement count
        return result; // Return pointer to removed object
      }
      i = i + 1;
      poolPtr = poolPtr + 1;
    } while (i < count);
  }
  return 0; // Not found
}