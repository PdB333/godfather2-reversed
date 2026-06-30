// FUNC_NAME: GrowingArray::pushBack
// Address: 0x004ae650
// Role: Adds a 32-byte element to the end of a dynamically growing array.
//        The array structure has fields: buffer (+0x00), size (+0x04), capacity (+0x08).
//        Each element is exactly 0x20 (32) bytes.
//        Growth policy: if capacity == 0, set to 1; else double.
//        Calls FUN_004ae910 (reallocation routine) when capacity is insufficient.
// EDI holds pointer to the 32-byte element to copy.

struct GrowingArray
{
    void*   buffer;   // +0x00: pointer to contiguous element array
    int     size;     // +0x04: number of elements currently stored
    int     capacity; // +0x08: allocated element capacity (elements, not bytes)
};

void __thiscall GrowingArray::pushBack(const void* element)
{
    GrowingArray* thisArray = this; // implicit this in EAX
    int currentSize = thisArray->size;
    int cap = thisArray->capacity;

    // If full, grow the container
    if (currentSize == cap)
    {
        int newCap;
        if (cap == 0)
            newCap = 1;
        else
            newCap = cap * 2;
        // Call reallocation function (likely reallocates buffer to newCap elements)
        FUN_004ae910(newCap); // Reallocate array to new capacity
    }

    // Compute target slot and copy 32 bytes from element
    char* dest = static_cast<char*>(thisArray->buffer) + (thisArray->size * 32);
    const char* src = static_cast<const char*>(element);
    if (dest != nullptr) // always true after growth, but check retained from original
    {
        // Copy 4 qwords (32 bytes total) – element is 0x20 in size
        *reinterpret_cast<unsigned long long*>(dest + 0) = *reinterpret_cast<const unsigned long long*>(src + 0);
        *reinterpret_cast<unsigned long long*>(dest + 8) = *reinterpret_cast<const unsigned long long*>(src + 8);
        *reinterpret_cast<unsigned long long*>(dest + 16) = *reinterpret_cast<const unsigned long long*>(src + 16);
        *reinterpret_cast<unsigned long long*>(dest + 24) = *reinterpret_cast<const unsigned long long*>(src + 24);
    }

    thisArray->size++;
}