// FUNC_NAME: ObjectManager::removeObjectByID
void __thiscall ObjectManager::removeObjectByID(int this, int objectID)
{
  uint count;
  uint *objectPtr;
  uint i;
  int **objectArray;
  
  count = *(uint *)(this + 0x1c);
  i = 0;
  if (count != 0) {
    objectArray = *(int ***)(this + 0x18); // +0x18: array of object pointers
    while (*(int *)(*objectArray + 0xc) != objectID) { // +0x0c: object ID field
      i = i + 1;
      objectArray = objectArray + 1;
      if (count <= i) {
        return;
      }
    }
    if (-1 < (int)i) {
      objectPtr = (uint *)(*(int **)(this + 0x18))[i];
      if (*(char *)(this + 0x11) != '\0') { // +0x11: flag for "isDestroying" or similar
        *objectPtr = *objectPtr | 0x40; // mark object as pending removal
        return;
      }
      if (i != count - 1) {
        *(undefined4 *)(*(int *)(this + 0x18) + i * 4) =
             *(undefined4 *)(*(int *)(this + 0x18) + -4 + count * 4);
      }
      *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + -1; // decrement count
      if (objectPtr != (uint *)0x0) {
        FUN_0090d920(); // likely release/cleanup
        FUN_009c8eb0(objectPtr); // likely free memory
      }
      FUN_0090df00(); // likely notify removal
    }
  }
  return;
}