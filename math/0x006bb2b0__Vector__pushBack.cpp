// FUNC_NAME: Vector::pushBack
// Address: 0x006bb2b0
// Role: Appends an element to a dynamic array (vector), resizing if necessary.
// Structure: this[0] = data pointer, this[1] = size, this[2] = capacity

void __thiscall Vector::pushBack(int *this, undefined4 *valuePtr)
{
    int *data = (int *)this[0]; // +0x00: pointer to element array
    int size = this[1];         // +0x04: current number of elements
    int capacity = this[2];     // +0x08: allocated capacity

    if (size == capacity)
    {
        // Grow capacity: double if non-zero, else set to 1
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Call reallocation function (likely realloc or grow)
        FUN_006ba8b0(newCapacity);
        // Note: after reallocation, this[0] and this[2] are updated by the callee
    }

    // Write the new value at the end
    int *slot = (int *)(this[0] + size * 4);
    this[1] = size + 1;
    if (slot != (int *)0x0)
    {
        *slot = *valuePtr;
    }
}