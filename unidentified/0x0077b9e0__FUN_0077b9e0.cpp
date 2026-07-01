// FUNC_NAME: SomeContainer::pushBackPair
void __thiscall SomeContainer::pushBackPair(int *this, undefined4 *pairData)
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
    FUN_0077b550(capacity); // reallocate container
  }
  slot = (undefined4 *)(*this + this[1] * 8);
  this[1] = this[1] + 1;
  if (slot != (undefined4 *)0x0) {
    *slot = *pairData;
    slot[1] = pairData[1];
  }
  return;
}