// FUNC_NAME: ObjectPool::findByKey
int __thiscall ObjectPool::findByKey(int this, int *key)
{
  int object;
  int *poolPtr;
  uint index;
  
  index = 0;
  if (*(uint *)(this + 0xc) != 0) {
    poolPtr = *(int **)(this + 8); // +0x8: pointer to pool array
    do {
      object = *poolPtr;
      // Compare 4 ints at offsets +0x1c, +0x20, +0x24, +0x28 as the key
      if ((((*(int *)(object + 0x1c) == *key) && 
            (*(int *)(object + 0x20) == key[1])) &&
           (*(int *)(object + 0x24) == key[2])) && 
           (*(int *)(object + 0x28) == key[3])) {
        return object;
      }
      index = index + 1;
      poolPtr = poolPtr + 1;
    } while (index < *(uint *)(this + 0xc)); // +0xc: count of objects in pool
  }
  return 0;
}