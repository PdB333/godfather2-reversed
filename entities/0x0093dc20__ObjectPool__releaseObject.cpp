// FUNC_NAME: ObjectPool::releaseObject
void __thiscall ObjectPool::releaseObject(int this, undefined4 *object)
{
  int objectType;
  int objectData;
  
  objectType = object[2]; // +0x8: object type field
  if ((((objectType == 1) || (objectType == 2)) && (objectData = object[8], objectData != 0)) ||
     (((objectType == 5 && (objectData = object[8], objectData != 0)) ||
      ((objectType == 6 && (objectData = object[8], objectData != 0)))))) {
    FUN_009c8f10(objectData); // likely cleanup/destructor for specific types
  }
  *object = *(undefined4 *)(this + 0x34); // +0x34: free list head pointer
  *(int *)(this + 0x10) = *(int *)(this + 0x10) + -1; // +0x10: active object count
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1; // +0xc: freed object count
  *(undefined4 **)(this + 0x34) = object; // push object onto free list
  return;
}