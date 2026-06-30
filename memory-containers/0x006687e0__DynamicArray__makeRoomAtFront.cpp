// FUNC_NAME: DynamicArray::makeRoomAtFront
// Address: 0x006687e0
// This function inserts empty slots at the front of a dynamic array by shifting existing elements to the right.
// The array structure (offsets from this):
//   +0x00: mCount (int) - number of occupied elements
//   +0x04: mCapacity (int) - allocated capacity (in elements)
//   +0x08: unused? (not referenced)
//   +0x0C: mData (int*) - pointer to element data
// Returns 0 on success; returns non-zero (from realloc) if reallocation occurred (callers handle accordingly?).

int DynamicArray::makeRoomAtFront(int numSlots)
{
    // Check if there is enough capacity
    if (numSlots > 0) {
        // If we need more room, try to reallocate
        if (mCapacity < mCount + numSlots) {
            int reallocResult = reallocBuffer(); // FUN_00667740 - likely grows capacity
            if (reallocResult != 0) {
                // Reallocation succeeded; early return (maybe returns new capacity?)
                return reallocResult;
            }
        }

        // Increase element count by the number of slots to make room
        mCount += numSlots;
        int newCount = mCount;

        // Shift existing elements to the right by numSlots positions (starting from the end)
        int* dest = mData + newCount - 1;          // pointer to last element of new array
        int* src  = mData + newCount - numSlots - 1; // pointer to last element of old array
        int numToShift = newCount - numSlots;      // number of elements to shift
        for (int i = 0; i < numToShift; ++i) {
            *dest = *src;
            --dest;
            --src;
        }

        // Zero out the newly created front slots
        int* front = mData;
        for (int i = 0; i < numSlots; ++i) {
            *front = 0;
            ++front;
        }
    }
    return 0;
}