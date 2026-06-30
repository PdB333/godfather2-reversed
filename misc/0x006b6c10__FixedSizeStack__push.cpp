// FUNC_NAME: FixedSizeStack::push
void __thiscall FixedSizeStack::push(uint *this, uint *item)
{
  uint count;
  uint *slot;
  
  count = *this;
  if (count < 4) {
    slot = this + count * 5 + 1; // +0x04 base of slots, each slot is 5 uint32s (20 bytes)
    *this = count + 1;            // increment count
    *slot = *item;                // copy item data (5 uint32s)
    slot[1] = item[1];
    slot[2] = item[2];
    slot[3] = item[3];
  }
  return;
}