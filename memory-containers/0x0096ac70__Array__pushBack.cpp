// FUNC_NAME: Array::pushBack
void __thiscall Array::pushBack(int *this, undefined4 *element)
{
  int *buffer; // pointer to allocated buffer
  int size;    // current number of elements
  int capacity; // allocated capacity

  size = this[1];    // +0x04
  capacity = this[2]; // +0x08

  if (size == capacity) {
    // Need to grow the array
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity = capacity * 2;
    }
    // Reallocate to new capacity (FUN_00963c70 likely does the reallocation)
    FUN_00963c70(capacity);
  }

  // Write the new element at the end
  buffer = (int *)this[0]; // +0x00
  buffer[size] = *element;
  this[1] = size + 1; // increment size
}