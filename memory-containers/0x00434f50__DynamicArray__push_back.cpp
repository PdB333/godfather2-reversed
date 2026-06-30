// FUNC_NAME: DynamicArray::push_back

class DynamicArray {
public:
    int*    data;      // +0x00 : pointer to element array
    int     size;      // +0x04 : number of elements currently stored
    int     capacity;  // +0x08 : allocated capacity (number of elements)

    // Inserts a new element at the end, growing the array if necessary.
    // __thiscall, EAX = this, stack param = value
    void push_back(int value);
    
private:
    // Called to reallocate internal buffer to at least newCapacity elements.
    // (Ghidra callee FUN_00435050)
    void grow(int newCapacity);
};

void DynamicArray::push_back(int value) {
    // Check if we need to grow
    if (size == capacity) {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        grow(newCap); // reallocate internal buffer
    }

    // Compute pointer to the slot just past the last element
    int* slot = data + size;  // +0x00 + size*4

    // Increment size before writing (decompiler shows increment then write,
    // but the pointer was computed with the old size)
    size++;

    // Write the new element (defensive null check, though slot should never be null)
    if (slot != nullptr) {
        *slot = value;
    }
}