// FUNC_NAME: Vector::push_back

void __thiscall Vector::push_back(int *this, undefined4 *value)
{
  int capacity = this[2];
  int size = this[1];
  
  // Check if we need to grow the array
  if (size == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    // Resize internal buffer (function at 0x006f9120)
    resizeInternal(capacity);
  }
  
  // Get pointer to the next free slot
  int *slot = (int *)(this[0] + size * 4);
  // Increment size
  this[1] = size + 1;
  
  // Copy the value into the slot (only if slot is non-null)
  if (slot != (int *)0x0) {
    *slot = *value;
  }
}