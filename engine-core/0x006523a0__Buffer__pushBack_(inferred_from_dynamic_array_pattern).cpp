// FUNC_NAME: Buffer::pushBack (inferred from dynamic array pattern)
// Address: 0x006523a0
// This function appends a 4-byte value to a dynamic buffer.
// The buffer is controlled by a structure at this+0x14, containing:
//   +0x00: data pointer (start)
//   +0x04: write pointer (current insertion point)
//   +0x08: end pointer (capacity limit)
//   +0x0C: growth threshold (e.g., resize step size)
// When the buffer is full (write >= end) and the element count has reached
// the growth threshold, the buffer is expanded via growBuffer().
// After a grow, the end pointer is set to the new write pointer,
// making the buffer exactly sized for the new element.

void __thiscall Buffer::pushBack(int *this, int *value)
{
  int *controlBlock = *(int **)(this + 0x14);
  int *writePtr = (int *)controlBlock[1];
  int *endPtr = (int *)controlBlock[2];
  int *startPtr = (int *)controlBlock[0];

  // Fast path: buffer has room
  if ((uint)writePtr < (uint)endPtr) 
  {
    *writePtr = *value;
    controlBlock[1] = (int)(writePtr + 1);
    return;
  }

  // Check if growth is needed (current element count >= growth threshold)
  int elementCount = (writePtr - startPtr) / 4;  // number of elements already stored
  if (controlBlock[3] <= elementCount) 
  {
    growBuffer();  // FUN_00b97aea - expands the buffer (updates controlBlock pointers)
  }

  // After growth (or if growth was not triggered but buffer was full – 
  // growth must have been performed by growBuffer() to make room)
  writePtr = (int *)controlBlock[1];
  if (writePtr != (int *)0x0) 
  {
    *writePtr = *value;
  }
  // Advance write pointer and set end pointer to the new write location
  controlBlock[1] = (int)(writePtr + 1);
  controlBlock[2] = controlBlock[1];
}