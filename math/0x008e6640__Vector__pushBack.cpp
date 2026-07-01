// FUNC_NAME: Vector::pushBack
// Address: 0x008e6640
// Role: Pushes a value onto the end of a dynamic array. If size equals capacity, doubles capacity (or sets to 1 if zero) via internal reserve call.
// Struct offsets: +0x00: data (int*), +0x04: size (int), +0x08: capacity (int)

void __thiscall Vector::pushBack(int* this, const uint32_t* valuePtr) {
    int capacity = this[2];    // +0x08
    int size = this[1];        // +0x04

    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Internal reserve function (FUN_008e5cf0) reallocates buffer
        this->reserve(newCapacity);  // calls FUN_008e5cf0
    }

    int* data = (int*)this[0]; // +0x00
    data[size] = *valuePtr;
    this[1] = size + 1;        // increment size
}