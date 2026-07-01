// FUNC_NAME: Vector4Array::pushBack
void __thiscall Vector4Array::pushBack(int *this, const int *element) {
    int curSize = this[1]; // +0x04 current number of elements
    int capacity = this[2]; // +0x08 allocated capacity
    if (curSize == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Grow the internal buffer to newCapacity (calls realloc or alloc function)
        FUN_008defe0(newCapacity);
    }
    // Calculate pointer to next slot (each element is 0x10 bytes)
    int *dest = (int *)(this[0] + curSize * 0x10); // base pointer + size * 16
    this[1] = curSize + 1; // increment count
    if (dest != nullptr) {
        dest[0] = element[0];
        dest[1] = element[1];
        dest[2] = element[2];
        dest[3] = element[3];
    }
}