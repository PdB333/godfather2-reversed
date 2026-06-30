// FUNC_NAME: SomeContainer::removeAt
void __fastcall SomeContainer::removeAt(int thisPtr, uint index)
{
  uint count = *(uint *)(thisPtr + 0x58); // +0x58: element count
  if (index < count) {
    if (index < count - 1) {
      // Shift the last element into the removed slot (swap-remove)
      *(undefined4 *)(thisPtr + 8 + index * 8) = *(undefined4 *)(thisPtr + count * 8);       // Copy first dword of last element
      *(undefined4 *)(thisPtr + 0xc + index * 8) = *(undefined4 *)(thisPtr + 4 + count * 8); // Copy second dword of last element
    }
    // Decrement count
    *(int *)(thisPtr + 0x58) = count - 1;
    // Zero out the now-unused last slot
    undefined4 *lastSlot = (undefined4 *)(thisPtr + 8 + (count - 1) * 8);
    if (lastSlot != (undefined4 *)0x0) {
      *lastSlot = 0;
      lastSlot[1] = 0;
    }
  }
  return;
}