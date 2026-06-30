// FUNC_NAME: ObjectList::remove
uint __thiscall ObjectList::remove(int thisPtr, int objectId)
{
  uint count;
  uint i;
  uint3 tmp;
  uint result;
  int *list;
  uint uVar5;
  
  count = *(uint *)(thisPtr + 0x14); // +0x14: count of objects in list
  uVar5 = 0;
  if (count != 0) {
    list = *(int **)(thisPtr + 0x10); // +0x10: pointer to array of object IDs
    do {
      if (*list == objectId) {
        if (-1 < (int)uVar5) {
          // Call destructor or release on the object
          FUN_006aa160(objectId);
          // If not the last element, move last element to this position
          if (uVar5 != *(int *)(thisPtr + 0x14) - 1U) {
            *(undefined4 *)(*(int *)(thisPtr + 0x10) + uVar5 * 4) =
                 *(undefined4 *)(*(int *)(thisPtr + 0x10) + -4 + *(int *)(thisPtr + 0x14) * 4);
          }
          // Decrement count
          *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + -1;
          count = *(uint *)(thisPtr + 0x1c); // +0x1c: some iterator/index state
          tmp = (uint3)(count >> 8);
          if (uVar5 != count) {
            result = (uint)tmp << 8;
            if (count != *(uint *)(thisPtr + 0x14)) {
              return result;
            }
            *(uint *)(thisPtr + 0x1c) = uVar5;
            return result;
          }
          *(undefined4 *)(thisPtr + 0x1c) = 0xffffffff;
          return CONCAT31(tmp,1);
        }
        break;
      }
      uVar5 = uVar5 + 1;
      list = list + 1;
    } while (uVar5 < count);
  }
  return count & 0xffffff00;
}