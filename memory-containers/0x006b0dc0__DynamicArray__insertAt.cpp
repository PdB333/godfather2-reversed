// FUNC_NAME: DynamicArray::insertAt

// Reconstructed from Ghidra at 0x006b0dc0
// This function inserts an 8-byte element at the given index in a dynamic array.
// The array stores two 32-bit values per element (possibly a key/value pair).
// Internal structure:
//   +0x00: base pointer to array (void*)
//   +0x04: size (uint32)
//   +0x08: capacity (uint32)

void* __thiscall DynamicArray::insertAt(uint index)
{
    uint size = this->size;          // +0x04
    uint capacity = this->capacity;  // +0x08

    // Grow if full
    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;
        reallocate(capacity);   // FUN_006afba0
    }

    uint uVar2 = this->size;
    void* slot = reinterpret_cast<byte*>(this->base) + uVar2 * 8;  // pointer to new slot at end

    // If inserting at the end, just increment size and return slot
    if (index == uVar2)
    {
        this->size = uVar2 + 1;
        return slot;
    }

    // Otherwise shift elements right from index to end-1
    if (slot != nullptr)
    {
        // Copy the last element's data into the shifted slot (which is beyond old end)
        *reinterpret_cast<uint32*>(slot) = *reinterpret_cast<uint32*>(reinterpret_cast<byte*>(slot) - 8);
        *(reinterpret_cast<uint32*>(slot) + 1) = *(reinterpret_cast<uint32*>(reinterpret_cast<byte*>(slot) - 8) + 1);
    }

    uVar2 = this->size;  // reload size (might have been updated by realloc? but still old size)
    // Shift elements from (size-1) down to (index+1) to the right
    while (uVar2 -= 1, index < uVar2)
    {
        slot = reinterpret_cast<byte*>(this->base) + uVar2 * 8;
        *reinterpret_cast<uint32*>(slot) = *reinterpret_cast<uint32*>(reinterpret_cast<byte*>(slot) - 8);
        *(reinterpret_cast<uint32*>(slot) + 1) = *(reinterpret_cast<uint32*>(reinterpret_cast<byte*>(slot) - 8) + 1);
    }

    this->size = this->size + 1;  // increment size after shifting
    return reinterpret_cast<byte*>(this->base) + index * 8;
}