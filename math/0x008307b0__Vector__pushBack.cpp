// FUNC_NAME: Vector::pushBack
// Address: 0x008307b0
// Adds a new element to a dynamic array (custom vector) of 32-bit values.
// Object layout: +0x00 = buffer (int*), +0x04 = size (int), +0x08 = capacity (int)
void __thiscall Vector::pushBack(int* this, int* value) {
    int size = this[1];
    int capacity = this[2];

    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Reallocate internal buffer to new capacity
        reallocate(newCapacity); // FUN_0082bc20
    }

    int* targetSlot = (int*)(this[0] + this[1] * 4);
    this[1] = this[1] + 1;
    if (targetSlot != nullptr) {
        *targetSlot = *value;
    }
}