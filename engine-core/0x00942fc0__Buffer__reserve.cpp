// FUNC_NAME: Buffer::reserve
// Address: 0x00942fc0
// Role: Sets the capacity of an internal buffer; grows via reallocation if needed, otherwise shrinks capacity value without reallocating.

void __thiscall Buffer::reserve(uint newCapacity)
{
    uint currentCapacity = *(uint *)(this + 4);  // +0x04: m_capacity

    if (currentCapacity < newCapacity) {
        // Grow: call internal allocator to expand storage
        FUN_00941a80(newCapacity);  // presumably reallocate(buffer, newCapacity)
        *(uint *)(this + 4) = newCapacity;  // update capacity
        return;
    }

    if (newCapacity < currentCapacity) {
        // Shrink: just reduce capacity value; actual memory not freed here
        *(uint *)(this + 4) = newCapacity;
    }
}