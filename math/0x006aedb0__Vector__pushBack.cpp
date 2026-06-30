// FUNC_NAME: Vector::pushBack
// Function address: 0x006aedb0
// Role: Appends an element to a dynamic array (vector)
// Assumes class Vector with fields: mData (int*, offset 0), mSize (int, offset 4), mCapacity (int, offset 8)

class Vector {
private:
    int* mData;      // +0x00: pointer to allocated element array
    int mSize;       // +0x04: number of elements currently stored
    int mCapacity;   // +0x08: total allocated capacity (in elements)

    // Calls reallocation routine at 0x006ad8a0
    void grow(int newCapacity);

public:
    // __thiscall: this is the implicit 'this' pointer (param_1)
    void __thiscall pushBack(const int* value);
};

void Vector::pushBack(const int* value) {
    // Check if capacity exhausted; if so, grow
    if (mSize == mCapacity) {
        int newCapacity;
        if (mCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = mCapacity * 2;   // double capacity
        }
        grow(newCapacity);                 // FUN_006ad8a0
    }

    // Compute address of next slot (based on original data pointer + size)
    int* dest = mData + mSize;
    mSize++;

    // Only copy if destination is valid (defensive check)
    if (dest != nullptr) {
        *dest = *value;   // copy 4-byte value
    }
}