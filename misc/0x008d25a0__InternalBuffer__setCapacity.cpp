// FUNC_NAME: InternalBuffer::setCapacity
// Function at 0x008d25a0: Sets the capacity of an internal buffer. If new capacity is larger, reallocates memory via FUN_008d2380.
// Structure: InternalBuffer at +0x04 is capacity (uint).
void __thiscall InternalBuffer::setCapacity(uint newCapacity)
{
    // If new capacity is larger than current, reallocate
    if (newCapacity > this->capacity) // this+0x04
    {
        FUN_008d2380(newCapacity); // Reallocation function
        this->capacity = newCapacity; // +0x04
        return;
    }
    // If new capacity is smaller, just update the size (no shrink)
    if (newCapacity < this->capacity)
    {
        this->capacity = newCapacity;
    }
}