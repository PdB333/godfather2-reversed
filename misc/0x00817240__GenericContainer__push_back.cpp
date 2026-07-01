// FUNC_NAME: GenericContainer::push_back
void __thiscall GenericContainer::push_back(int *this, undefined4 *item)
{
  undefined4 *newSlot;
  int currentSize;
  
  currentSize = this[2]; // +0x08 capacity
  if (this[1] == currentSize) { // +0x04 count == capacity
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    FUN_00817000(currentSize); // reallocate internal buffer
  }
  newSlot = (undefined4 *)(*this + this[1] * 0x18); // +0x00 buffer + count * 24 bytes
  this[1] = this[1] + 1; // increment count
  if (newSlot != (undefined4 *)0x0) {
    *newSlot = *item;
    newSlot[1] = item[1];
    FUN_004d3b50(); // copy remaining 16 bytes (item[2]..item[5])? Or construct?
    return;
  }
  return;
}