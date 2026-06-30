// FUNC_NAME: DynamicArray::ensureCapacity
// Function address: 0x0066a620
// Role: Ensures the internal buffer is allocated to match the current capacity
// Reallocates data array if current size differs from capacity (i.e., buffer not yet sized to capacity)
// Returns 0 on success, -2 on realloc failure

int DynamicArray::ensureCapacity() // __thiscall, this in ESI
{
    // Structure offsets (relative to this):
    // +0x00: capacity (int) - allocated number of elements
    // +0x04: size (int) - current number of elements
    // +0x08: (unused field, possibly pad or other)
    // +0x0C: data (int*) - pointer to element array

    if (size != capacity) {
        // Reallocate buffer to hold 'capacity' ints
        void* newBuffer = _realloc(data, capacity * sizeof(int));
        if (newBuffer == nullptr) {
            return -2; // 0xfffffffe
        }
        data = static_cast<int*>(newBuffer);
        size = capacity; // after realloc, size matches capacity
    }
    return 0;
}