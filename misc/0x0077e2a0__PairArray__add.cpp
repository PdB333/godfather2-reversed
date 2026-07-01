// FUNC_NAME: PairArray::add
// Address: 0x77e2a0
// Role: Appends a 2-element pair (8 bytes) to a dynamically growing array.
// The array structure: [0x00] data pointer, [0x04] count, [0x08] capacity.
// Each element is two int32/float values (8 bytes).
// If the array is full, capacity is doubled (or set to 1 if initially 0).

void __thiscall PairArray::add(int *this, int pair[2])
{
  int capacity = this[2];
  int count = this[1];
  int *data = (int *)this[0];

  if (count == capacity) {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    // FUN_0x0077d9b0 reallocates the data buffer to hold newCapacity elements.
    // Presumably returns a new pointer or modifies this[0] internally.
    FUN_0077d9b0(newCapacity);
    // Note: after realloc, this[0] and this[2] are updated elsewhere.
  }

  // Write pair at the end of the array
  int *slot = (int *)(this[0] + this[1] * 8); // element size = 8
  this[1] = this[1] + 1; // increment count
  if (slot != (int *)0x0) {
    slot[0] = pair[0];
    slot[1] = pair[1];
  }
}