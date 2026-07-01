// FUNC_NAME: ObjectPool::releaseAll
void __fastcall ObjectPool::releaseAll(int *this)
{
  int count;
  int index;
  int *slotPtr;
  int *refCountPtr;
  
  count = this[1] + -1;
  if (-1 < count) {
    index = count * 0x2c;
    do {
      slotPtr = (int *)(index + 0x10 + *this); // +0x10: start of slot array, each slot 0x2c bytes
      if (*slotPtr != 0) {
        refCountPtr = (int *)(*slotPtr + 4); // +0x04: reference count field
        *refCountPtr = *refCountPtr + -1;
        if (((int *)*slotPtr)[1] == 0) { // if reference count becomes zero
          (**(code **)(*(int *)*slotPtr + 4))(); // call virtual destructor at vtable+4
        }
        *slotPtr = 0;
      }
      count = count + -1;
      index = index + -0x2c;
    } while (-1 < count);
  }
  if (*this != 0) {
    FUN_009c8f10(*this); // likely operator delete[] or memory deallocation
  }
  return;
}