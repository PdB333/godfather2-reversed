// FUNC_NAME: RandomPool::generateUniqueRandomSequence
int __fastcall RandomPool::generateUniqueRandomSequence(int *this)
{
  uint randVal;
  int result;
  undefined4 *src;
  undefined4 *dst;
  int *poolPtr;
  
  this[2] = 0; // currentIndex = 0
  *this = 0;   // count = 0
  _memset((void *)this[3], 0, this[1] * 4); // clear pool array (size * 4 bytes)
  
  if (in_EAX < 1) {
    return 0;
  }
  
  do {
    randVal = _rand();
    result = (randVal ^ (int)randVal >> 0x1f) - ((int)randVal >> 0x1f); // abs(rand)
  } while (result == 0); // ensure non-zero
  
  result = FUN_00665820(this, result, this); // try to insert random value
  if (result == 0) {
    while ((in_EAX = in_EAX + -1, *this + 1 <= this[1] || (result = FUN_00667740(), result == 0))) {
      *this = *this + 1; // increment count
      result = *this;
      src = (undefined4 *)(this[3] + -4 + result * 4); // source = pool[count-1]
      dst = (undefined4 *)(this[3] + -8 + result * 4); // dest = pool[count-2]
      result = result + -1; // shift count
      if (0 < result) {
        do {
          *src = *dst; // shift elements right
          src = src + -1;
          dst = dst + -1;
          result = result + -1;
        } while (result != 0);
      }
      *(undefined4 *)this[3] = 0; // pool[0] = 0
      poolPtr = this;
      randVal = _rand();
      result = FUN_00665820(this, (randVal ^ (int)randVal >> 0x1f) - ((int)randVal >> 0x1f), poolPtr);
      if (result != 0) {
        return result;
      }
      if (in_EAX < 1) {
        return 0;
      }
    }
  }
  return result;
}