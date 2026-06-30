// FUNC_NAME: Array::operatorAssign
void Array::operatorAssign(int *otherPtr)
{
  int *thisPtr;
  uint otherSize;
  int *otherArrayPtr;
  int capacity;
  int *destPtr;
  uint idx;

  thisPtr = (int *)this;
  if (thisPtr != otherPtr) {
    otherSize = (uint)otherPtr[1];               // other.size
    idx = 0;
    if (thisPtr[1] != 0) {                       // if this.size != 0
      thisPtr[1] = 0;                            // clear size
    }
    _ensureCapacity(thisPtr, (int)otherSize);     // pre-allocate at least otherSize
    if (otherSize != 0) {
      do {
        otherArrayPtr = (int *)*otherPtr;         // other.data
        capacity = thisPtr[2];                    // this.capacity
        if (thisPtr[1] == capacity) {            // if this.size == capacity -> double
          if (capacity == 0) {
            capacity = 1;
          }
          else {
            capacity = capacity * 2;
          }
          _ensureCapacity(thisPtr, capacity);    // double capacity
        }
        destPtr = (int *)(*thisPtr + thisPtr[1] * 4); // &this.data[this.size]
        thisPtr[1] = thisPtr[1] + 1;            // ++this.size
        if (destPtr != NULL) {
          *destPtr = *(int *)(otherArrayPtr + idx); // copy element
        }
        idx = idx + 1;
      } while (idx < otherSize);
    }
  }
  return;
}