// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int* this, int* value) {
    int newCapacity;
    int* dest;

    // Check if size == capacity (offsets: data+0, size+4, capacity+8)
    if (this[1] == this[2]) {
        // Grow: if capacity is 0, set to 1; otherwise double
        if (this[2] == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this[2] * 2;
        }
        // Reallocate internal buffer (FUN_0082b020 expands the vector, updating data pointer and capacity)
        FUN_0082b020(newCapacity);
    }

    dest = (int*)(this[0] + this[1] * 4); // data + size * sizeof(int)
    this[1] = this[1] + 1; // Increment size
    if (dest != (int*)0x0) {
        *dest = *value; // Copy the value into the new slot
    }
}