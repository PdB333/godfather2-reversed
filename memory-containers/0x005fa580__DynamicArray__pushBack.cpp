// FUNC_NAME: DynamicArray::pushBack
// Address: 0x005fa580
// Role: Push a 32-bit value onto the back of a dynamic array. Doubles capacity when full.
// Class layout: +0x00 = buffer (int*), +0x04 = size (int), +0x08 = capacity (int)

void __thiscall DynamicArray::pushBack(void* thisPtr, int value) {
    int* this = (int*)thisPtr;
    int size = this[1];
    int capacity = this[2];

    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate the internal buffer (calls FUN_005fa940)
        resize(newCapacity);
    }

    int* buffer = (int*)this[0];
    int* slot = &buffer[size];
    if (slot != nullptr) {
        *slot = value;
    }
    this[1] = size + 1;
}