// FUNC_NAME: VectorQueue::push_back
void __thiscall VectorQueue::push_back(int *this, undefined8 *item)
{
  undefined8 *dest;
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00833dd0(capacity);  // reallocate or grow internal array (likely grow)
  }
  dest = (undefined8 *)(*this + this[1] * 0xc);
  this[1] = this[1] + 1;
  if (dest != (undefined8 *)0x0) {
    *dest = *item;  // copy 8 bytes (first part of 12-byte element)
    *(undefined4 *)(dest + 1) = *(undefined4 *)(item + 1);  // copy remaining 4 bytes
  }
  return;
}