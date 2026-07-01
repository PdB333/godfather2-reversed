// FUNC_NAME: Container::pushBack
void __thiscall Container::pushBack(int *this, unsigned int *element)
{
    unsigned int *dataPtr;
    int capacity;
    
    capacity = this[2]; // capacity at offset +0x08
    if (this[1] == capacity) { // size == capacity -> need growth
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // grow the internal buffer to the new capacity
        // FUN_00963c10 likely performs reallocation or allocation of capacity elements
        FUN_00963c10(capacity);
    }
    // Get pointer to the next element slot (base + size * elementSize)
    dataPtr = (unsigned int *)(*this + this[1] * 4); // offset +0x00 = base pointer, +0x04 = size
    this[1] = this[1] + 1; // increase size
    if (dataPtr != (unsigned int *)0x0) {
        *dataPtr = *element; // copy the element (4 bytes)
    }
    return;
}