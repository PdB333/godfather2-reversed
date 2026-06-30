// FUNC_NAME: MemoryPool::free
undefined4 __fastcall MemoryPool::free(undefined4 this, undefined4 *ptr)
{
  int *node;
  undefined4 result;
  int *pool;
  int *poolList;
  
  result = 0;
  if ((ptr != (undefined4 *)0x0) && (pool = (int *)*(int *)((int)this + 0x1c), pool != (int *)0x0)) {
    while ((ptr < (undefined4 *)pool[2] || ((undefined4 *)pool[3] <= ptr))) {
      pool = (int *)pool[1];
      if (pool == (int *)0x0) {
        return result;
      }
    }
    *ptr = *(undefined4 *)pool[2];
    *(undefined4 **)pool[2] = ptr;
    node = pool + 4;
    *node = *node + -1;
    if ((*node == 0) && (*(char *)((int)this + 5) == '\0')) {
      if (*pool == 0) {
        *(int *)((int)this + 0x1c) = pool[1];
      }
      else {
        *(int *)(*pool + 4) = pool[1];
      }
      if ((int *)pool[1] != (int *)0x0) {
        *(int *)pool[1] = *pool;
      }
      (**(code **)(*(int *)this + 8))(pool);
      *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + -1;
    }
    result = 1;
  }
  return result;
}