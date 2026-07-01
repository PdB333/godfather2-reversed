// FUNC_NAME: EARSBuffer::setCapacity
// Function address: 0x008d2570
// Sets the capacity of a dynamic buffer. If new capacity is larger than current,
// reallocates internal storage. If smaller, just updates the capacity value.
// Offset +0x04: capacity (uint)

void __thiscall EARSBuffer::setCapacity(uint newCapacity)
{
    uint currentCapacity = *(uint *)(this + 4); // +0x04 capacity

    if (currentCapacity < newCapacity) {
        // Need to grow: reallocate internal buffer to accommodate new capacity
        FUN_008be050(newCapacity); // reallocate(newCapacity)
        *(uint *)(this + 4) = newCapacity;
        return;
    }
    if (newCapacity < currentCapacity) {
        // Shrinking: just update capacity, no reallocation needed
        *(uint *)(this + 4) = newCapacity;
    }
    // If equal, do nothing
}