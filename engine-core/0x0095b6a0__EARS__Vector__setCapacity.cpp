// FUNC_NAME: EARS::Vector::setCapacity
// Address: 0x0095b6a0
// Sets the capacity of a dynamic array, reallocating if the new capacity is larger.
void __thiscall setCapacity(uint newCapacity)
{
    // Offset +0x4: current allocated capacity
    uint &capacity = *(uint *)(this + 4);

    if (capacity < newCapacity) {
        // Grow: reallocate storage to fit new capacity
        reallocateStorage(newCapacity);  // calls FUN_00486800 (likely a realloc wrapper)
        capacity = newCapacity;
        return;
    }

    if (newCapacity < capacity) {
        // Shrink: just update capacity (no reallocation or shrink-to-fit)
        capacity = newCapacity;
    }
}