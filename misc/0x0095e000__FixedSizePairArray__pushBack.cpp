// FUNC_NAME: FixedSizePairArray::pushBack
void __thiscall FixedSizePairArray::pushBack(int *this, undefined4 *pair)
{
  undefined4 *slot;
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FixedSizePairArray::resize(capacity); // FUN_0095c7f0 - reallocate with new capacity
  }
  slot = (undefined4 *)(*this + this[1] * 8); // +0x0: data pointer, +0x4: count, +0x8: capacity
  this[1] = this[1] + 1; // increment count
  if (slot != (undefined4 *)0x0) {
    *slot = *pair;          // copy first 4 bytes of pair
    slot[1] = pair[1];      // copy second 4 bytes of pair (total 8 bytes per element)
  }
  return;
}