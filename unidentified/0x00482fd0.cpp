// FUN_00482fd0: TArray::insert
// Insert an 8-byte element at the given index, shifting subsequent elements right.
// Returns a pointer to the slot where the new element should be written.
// The array structure at 'this' : +0x00 data (uint8_t*), +0x04 size (int), +0x08 capacity (int)

int __thiscall TArray::insert(int index) {
    int* pSize   = reinterpret_cast<int*>(this + 4);
    int* pCap    = reinterpret_cast<int*>(this + 8);
    uint8_t* &data = *reinterpret_cast<uint8_t**>(this);
    int size = *pSize;
    int cap  = *pCap;

    // Grow if full
    if (size == cap) {
        int newCap = (cap == 0) ? 1 : cap * 2;
        // FUN_00483180 likely calls reserve(newCap) to reallocate
        reserve(newCap);
        // Update pointer and capacity after reallocation (reserve updates them)
        data = *reinterpret_cast<uint8_t**>(this);
        *pCap = newCap;
    }

    // Get current size again (might have changed if reallocation was called)
    size = *pSize;

    if (index != size) {
        // Not appending at the end: shift elements to make room

        // Copy the last element to the new slot at the end (one past current size)
        uint32_t* pLast = reinterpret_cast<uint32_t*>(data + size * 8);
        if (pLast != nullptr) {
            pLast[0] = pLast[-2]; // copy first 4 bytes of the last element
            pLast[1] = pLast[-1]; // copy second 4 bytes
        }

        // Shift elements from index+1 to size-1 one position to the right
        int i = size - 1;
        while (index < i) {
            uint32_t* pSlot = reinterpret_cast<uint32_t*>(data + i * 8);
            pSlot[0] = *reinterpret_cast<uint32_t*>(data + (i-1) * 8);
            pSlot[1] = *(reinterpret_cast<uint32_t*>(data + (i-1) * 8) + 1);
            i--;
        }
    }

    // Increase size
    *pSize = (*pSize) + 1;

    // Return pointer to the insertion slot
    return reinterpret_cast<int>(data + index * 8);
}