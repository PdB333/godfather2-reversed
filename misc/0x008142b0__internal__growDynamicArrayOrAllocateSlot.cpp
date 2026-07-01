// FUNC_NAME: internal::growDynamicArrayOrAllocateSlot
int __fastcall internal::growDynamicArrayOrAllocateSlot(int *this) // this = param_1, dynamic array structure
{
  undefined4 *pSlot;
  int capacity;
  
  capacity = this[2]; // +0x08: capacity (max number of elements)
  if (this[1] == capacity) { // +0x04: current element count
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00814020(capacity); // reallocate/resize internal buffer
  }
  pSlot = (undefined4 *)(*this + this[1] * 8); // +0x00: pointer to data buffer, each element is 8 bytes
  if (pSlot != (undefined4 *)0x0) {
    *pSlot = 0xfe16702f; // write magic value 0xFE16702F as first 4 bytes of slot
  }
  pSlot = (undefined4 *)(*this + this[1] * 8);
  // increment element count
  this[1] = this[1] + 1;
  // return pointer to the allocated slot
  return *this + (this[1] - 1) * 8;
}