// FUNC_NAME: Buffer::setCapacity
void __thiscall Buffer::setCapacity(uint newCapacity) {
    // Compare new capacity with current capacity (stored at offset +0x4)
    if (currentCapacity < newCapacity) {
        // Need to reallocate to larger buffer
        reallocateBuffer(newCapacity); // FUN_00949490
        currentCapacity = newCapacity;
        return;
    }
    if (newCapacity < currentCapacity) {
        // Shrinking capacity: only update the member, no reallocation
        currentCapacity = newCapacity;
    }
    return;
}