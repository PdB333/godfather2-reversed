// FUNC_NAME: Array::removeAt
// Function address: 0x008e5de0
//
// Removes the element at the given index by shifting all subsequent elements left
// and decrementing the element count. Assumes elements are 4 bytes wide.
// No reallocation or destruction is performed.
//
// Structure layout:
//   +0x00: uint32* pData  (pointer to array of 4‑byte elements)
//   +0x04: uint32   count (number of valid elements)

void __thiscall Array::removeAt(void* this, uint32 index)
{
  uint32* pData = *(uint32**)this;            // +0x00: pointer to array
  uint32 count = *(uint32*)((uint32*)this + 1); // +0x04: current element count

  // Shift all elements from [index+1 .. count-1] one slot left,
  // but only if index is not the last valid position.
  if (index < count - 1U)
  {
    do {
      pData[index] = pData[index + 1];
      index++;
    } while (index < count - 1U);
  }

  // Decrease the count by one, effectively removing the slot.
  *(uint32*)((uint32*)this + 1) = count - 1U;
}