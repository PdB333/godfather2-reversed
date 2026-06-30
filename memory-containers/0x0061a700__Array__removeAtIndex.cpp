// FUNC_NAME: Array::removeAtIndex
void __fastcall Array::removeAtIndex(int *this, uint index)
{
  int count;
  int *data;
  int bytesPerElement;
  
  count = this[1]; // +0x04: number of elements
  data = (int *)this[0]; // +0x00: pointer to array
  // Element size is 0x14 (20 bytes)
  
  if (index < count - 1) {
    // Shift remaining elements left by one slot
    do {
      *data = data[5];           // Copy first int of next element
      data[1] = data[6];         // Copy second int
      data[2] = data[7];         // Copy third int
      data[3] = data[8];         // Copy fourth int
      data[4] = data[9];         // Copy fifth int
      data += 5;                 // Advance by 20 bytes (5 ints)
      index++;
    } while (index < count - 1U);
  }
  
  this[1] = count - 1; // Decrement element count
  return;
}