// FUNC_NAME: GrowingArray::append_0x2c4_struct
void __thiscall FUN_007a6f10(int *this, undefined4 *data)
{
  int newCap;
  undefined4 *dest;
  
  newCap = this[2]; // +0x08 capacity
  if (this[1] == newCap) { // +0x04 size
    if (newCap == 0) {
      newCap = 1;
    }
    else {
      newCap = newCap * 2;
    }
    FUN_0079b040(newCap); // reallocate with new capacity (element size 0x2c4)
  }
  dest = (undefined4 *)(this[1] * 0x2c4 + *this); // +0x00 data pointer, element size = 0x2c4 (708 bytes)
  this[1] = this[1] + 1; // increment size
  if (dest != (undefined4 *)0x0) {
    for (int i = 0xb1; i != 0; i = i + -1) { // copy 0xb1 * 4 = 0x2c4 bytes
      *dest = *data;
      data = data + 1;
      dest = dest + 1;
    }
  }
  return;
}