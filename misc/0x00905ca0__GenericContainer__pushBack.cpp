// FUNC_NAME: GenericContainer::pushBack
void __thiscall GenericContainer::pushBack(int *this, int element)
{
  int capacity;
  
  capacity = this[2];
  if (this[1] == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_00905ac0(capacity); // likely reallocate/grow
  }
  // Calculate destination pointer: base + (count * elementSize)
  // elementSize = 0x1c (28 bytes)
  int dest = *this + this[1] * 0x1c;
  this[1] = this[1] + 1; // increment count
  if (dest != 0) {
    FUN_004d3b50(element); // likely copy constructor or memcpy
    *(undefined4 *)(dest + 0x10) = *(undefined4 *)(element + 0x10);
    *(undefined1 *)(dest + 0x14) = *(undefined1 *)(element + 0x14);
    *(undefined4 *)(dest + 0x18) = *(undefined4 *)(element + 0x18);
  }
  return;
}