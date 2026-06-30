//FUNC_NAME: Vector8::insert
// Function address: 0x005be0d0
// Role: Inserts a new element at the given index in a dynamic array of 8-byte elements.
// The array is stored as: [0] data pointer, [4] size, [8] capacity.
// Returns a pointer to the insertion slot (caller is expected to write the element there).

class Vector8 {
public:
    void* data;      // +0x00
    int size;        // +0x04
    int capacity;    // +0x08

    // Reallocate internal buffer to new capacity (called when size == capacity)
    void grow(int newCapacity); // FUN_005be230

    // Insert a slot at index 'index' (passed in EDI). Shifts elements right.
    // Returns pointer to the insertion slot.
    __thiscall void* insert(unsigned int index) {
        int* thisPtr = reinterpret_cast<int*>(this);
        int cap = thisPtr[2]; // capacity
        if (thisPtr[1] == cap) { // size == capacity
            if (cap == 0)
                cap = 1;
            else
                cap *= 2;
            grow(cap); // reallocate
        }

        unsigned int curSize = thisPtr[1]; // size
        if (index != curSize) {
            // Shift elements from size-1 down to index+1
            for (unsigned int i = curSize; i > index; --i) {
                int* dest = reinterpret_cast<int*>(thisPtr[0] + i * 8);
                int* src  = reinterpret_cast<int*>(thisPtr[0] + (i - 1) * 8);
                dest[0] = src[0];
                dest[1] = src[1];
            }
        }
        thisPtr[1] = curSize + 1; // increment size
        return reinterpret_cast<void*>(thisPtr[0] + index * 8);
    }
};