// FUNC_NAME: EARSArray::InsertAt
// Address: 0x006b0dc0
// Inserts a slot at the given index, shifting subsequent elements.
// Returns a pointer to the newly inserted element slot (8 bytes).
// The array structure: +0x00: data pointer (Element size = 8 bytes), +0x04: element count (size), +0x08: capacity

struct EARSArray
{
    void*   data;       // +0x00: pointer to contiguous array of 8-byte elements
    int32_t size;       // +0x04: number of elements currently stored
    int32_t capacity;   // +0x08: allocated element capacity
};

// Forward declaration – reallocation function at 0x006afba0
void Reallocate(int32_t newCapacity); // internal helper

void* __thiscall EARSArray::InsertAt(uint32_t index)
{
    // Verify capacity – grow if needed
    if (size == capacity)
    {
        int32_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Reallocate(newCapacity);
    }

    // If inserting at the end, just increase size and return the new slot
    if (index == size)
    {
        size++;
        return static_cast<uint8_t*>(data) + index * 8;
    }

    // Otherwise, we must open a gap at `index`:
    // 1. Copy the last element to the newly created slot at `size` (one past end)
    uint32_t* lastSlot = static_cast<uint32_t*>(data) + size * 2;          // each element is 2 uint32s
    lastSlot[0] = lastSlot[-2];   // copy both halves of last element
    lastSlot[1] = lastSlot[-1];

    // 2. Shift elements from `size-1` down to `index+1` to the right by one slot
    for (uint32_t i = size - 1; i > index; i--)   // while index < i
    {
        uint32_t* dst = static_cast<uint32_t*>(data) + i * 2;
        uint32_t* src = dst - 2;
        dst[0] = src[0];
        dst[1] = src[1];
    }

    // 3. Update size and return pointer to the now‑vacant slot at `index`
    size++;
    return static_cast<uint8_t*>(data) + index * 8;
}