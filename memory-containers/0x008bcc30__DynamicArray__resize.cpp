// FUNC_NAME: DynamicArray::resize
void __thiscall DynamicArray::resize(int *this, uint newSize)
{
  uint oldSize;
  undefined8 *elementPtr;
  int elementIndex;
  int numNewElements;
  
  if ((uint)this[1] < newSize) {
    FUN_008bc950(newSize);
    oldSize = this[1];
    if (oldSize < newSize) {
      elementIndex = oldSize * 0x2c;
      numNewElements = newSize - oldSize;
      do {
        elementPtr = (undefined8 *)(*this + elementIndex);
        if (elementPtr != (undefined8 *)0x0) {
          // Initialize new element with sentinel values
          *(undefined4 *)(elementPtr + 3) = 0xbadbadba;  // +0x0C: sentinel
          *(undefined4 *)((int)elementPtr + 0x1c) = 0xbeefbeef; // +0x1C: sentinel
          *(undefined4 *)(elementPtr + 4) = 0xeac15a55;  // +0x10: sentinel
          *(undefined4 *)((int)elementPtr + 0x24) = 0x91100911; // +0x24: sentinel
          *(undefined1 *)(elementPtr + 5) = 1;  // +0x28: some flag (set to 1)
          *(undefined1 *)((int)elementPtr + 0x29) = 0; // +0x29: some flag (set to 0)
          *elementPtr = 0;  // +0x00: first 8 bytes zeroed
          elementPtr[1] = 0; // +0x08: next 8 bytes zeroed
          elementPtr[2] = 0; // +0x10: next 8 bytes zeroed
        }
        elementIndex += 0x2c; // Each element is 0x2C (44) bytes
        numNewElements--;
      } while (numNewElements != 0);
      this[1] = newSize;
      return;
    }
  }
  else if ((uint)this[1] <= newSize) {
    return;
  }
  this[1] = newSize;
  return;
}