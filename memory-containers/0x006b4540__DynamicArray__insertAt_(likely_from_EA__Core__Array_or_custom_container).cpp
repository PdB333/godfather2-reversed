// FUNC_NAME: DynamicArray::insertAt (likely from EA::Core::Array or custom container)
// Address: 0x006b4540
// Role: Inserts an 8-byte element at the given index, shifting subsequent elements right.
// Structure: this[0] = data pointer (array of 8-byte elements), this[1] = current count, this[2] = capacity.

void* __thiscall DynamicArray::insertAt(uint index) {
    uint count = this[1];       // +0x04
    uint capacity = this[2];    // +0x08

    if (count == capacity) {
        // Expand capacity: double or set to 1 if empty.
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate the array (FUN_006b1f00 expects new capacity).
        FUN_006b1f00(capacity);
        // After reallocation, this[0] (data pointer) is updated by the reallocation function.
    }

    uint* data = (uint*)this[0];  // +0x00
    // Each element occupies 8 bytes (two 32-bit values).
    uint* slot = &data[index * 2];

    if (index == count) {
        // Appending at end: just increment count and return the next slot.
        this[1] = count + 1;
        return slot;
    }

    // Shift elements from index to count-1 one position to the right.
    // Note: slot already points to the target position.
    uint i = count; // Start from the current last element index.
    while (i > index) {
        // Move element at (i-1) to position i.
        data[i * 2] = data[(i - 1) * 2];
        data[i * 2 + 1] = data[(i - 1) * 2 + 1];
        i--;
    }

    this[1] = count + 1;  // Increment count after shift.
    return &data[index * 2]; // Return pointer to the now-vacated slot.
}