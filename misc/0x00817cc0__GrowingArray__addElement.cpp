// FUNC_NAME: GrowingArray::addElement
// Address: 0x00817cc0
// Role: Adds a new element to a dynamic array (growing array) with 12-byte elements.
// The element is initialized with two bytes of 0x2B and two zero int32 fields.
// Returns pointer to the newly added element.

class GrowingArray {
public:
    unsigned char* mData;     // +0x00: pointer to allocated data (element size = 12 bytes)
    int mCount;               // +0x04: current number of elements
    int mCapacity;            // +0x08: allocated capacity

    void* addElement();       // __thiscall, returns pointer to new element
};

// External helper: reallocate the internal buffer to new capacity.
void reallocateArray(int newCapacity);  // FUN_00817810

void* GrowingArray::addElement() {
    // Check if we need to grow the array.
    if (mCount == mCapacity) {
        int newCapacity = (mCapacity == 0) ? 1 : (mCapacity * 2);
        reallocateArray(newCapacity);  // Update mData, mCapacity, copy old elements
    }

    // Pointer to the new element at the end of the array.
    unsigned char* newElement = mData + mCount * 12;  // element size = 0xC

    // Initialize the new element's fields.
    newElement[0] = 0x2B;
    newElement[1] = 0x2B;
    *(int*)(newElement + 4) = 0;  // field at +0x04
    *(int*)(newElement + 8) = 0;  // field at +0x08

    // Increment count and return pointer to the newly added element.
    int oldCount = mCount;
    mCount = oldCount + 1;
    return mData + oldCount * 12;
}