// FUNC_NAME: Container::ensureCapacity
void __thiscall Container::ensureCapacity(int *this, uint requiredCapacity)
{
  undefined4 *newData;
  uint i;
  undefined4 *dst;

  // +0x00: data pointer
  // +0x04: count (number of elements)
  // +0x08: capacity (allocated element count)
  if ((uint)this[2] < requiredCapacity) {
    newData = (undefined4 *)operator new(requiredCapacity * 4); // allocate 4 bytes per element
    if (this[0] != 0) {
      i = 0;
      dst = newData;
      if (this[1] != 0) {
        do {
          if (dst != (undefined4 *)0x0) {
            *dst = *(undefined4 *)(this[0] + i * 4); // copy element
          }
          i = i + 1;
          dst = dst + 1;
        } while (i < (uint)this[1]);
      }
      operator delete((void *)this[0]); // free old data
    }
    this[0] = (int)newData;
    this[2] = requiredCapacity; // update capacity
  }
  return;
}