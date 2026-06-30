// FUNC_NAME: removeElementAtIndex
// Address: 0x00443990
// Role: Removes an element from an 8-byte aligned array buffer, shifting remaining elements left.
// The buffer structure: [0] pointer to element array, [1] number of elements.
// Each element is 8 bytes (e.g., an int pair or a pointer and an int).
void __fastcall removeElementAtIndex(uint index, int *buffer)
{
  // Remove element if not last
  if (index < (uint)(buffer[1] - 1)) {
    do {
      // Shift element at index+1 to index (8 bytes)
      *(undefined4 *)(*buffer + index * 8) = 
        *(undefined4 *)(*buffer + 8 + index * 8);
      *(undefined4 *)(*buffer + index * 8 + 4) = 
        *(undefined4 *)(*buffer + 8 + index * 8 + 4);
      index = index + 1;
    } while (index < (uint)(buffer[1] - 1));
  }
  // Decrement element count
  buffer[1] = buffer[1] - 1;
}