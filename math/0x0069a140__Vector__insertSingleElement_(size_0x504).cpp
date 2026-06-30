// FUNC_NAME: Vector::insertSingleElement (size 0x504)
void __thiscall Vector::insertSingleElement(void** this, void* position, void* source) {
    // this[0] = begin pointer, this[1] = end pointer, this[2] = capacity pointer
    byte** begin = (byte**)this;
    byte** end = (byte**)((int)this + 4);
    byte** capacity = (byte**)((int)this + 8);

    byte* currentEnd = *end;
    byte* currentCapacity = *capacity;

    if (currentEnd != currentCapacity) {
        // There's room; shift elements after insertion point if needed.
        // If source is within current range, adjust it for future shift.
        if ((position <= source) && (source < currentEnd)) {
            source = (byte*)((int)source + 0x504); // + element size
        }
        // Shift the last element forward by one element size.
        // (This is a memmove of one element from end-1 to end, but done via loop)
        if (currentEnd != nullptr) {
            byte* src = currentEnd - 0x504;
            byte* dst = currentEnd;
            for (int i = 0x141; i != 0; i--) { // 0x141 * 4 = 0x504
                *(uint32_t*)dst = *(uint32_t*)src;
                src += 4;
                dst += 4;
            }
        }
        // Shift the block from position to currentEnd-1 forwards by one element.
        // FUN_00699d80 is likely memmove(void* dst, void* src, size_t len)
        memmove(position, (byte*)((int)position + 0x504), (uint32_t)(currentEnd - (byte*)position));
        // Copy source element to the vacated spot.
        for (int i = 0x141; i != 0; i--) {
            *(uint32_t*)position = *(uint32_t*)source;
            source = (byte*)((int)source + 4);
            position = (byte*)((int)position + 4);
        }
        // Advance end pointer.
        *end = currentEnd + 0x504;
        return;
    }

    // Need to reallocate.
    int capacitySize = ((int)currentEnd - (int)*begin) / 0x504;
    int newCapacity;
    if (capacitySize == 0) {
        newCapacity = 1;
    } else {
        newCapacity = capacitySize * 2;
        if (newCapacity == 0) {
            newCapacity = 0; // would cause zero allocation? but goto in original
            // Original code had goto LAB_0069a216 which then jumped to allocation call.
            // So fall through.
        }
    }
    // Allocate new memory: size = newCapacity * 0x504
    void* newBuf = allocate(newCapacity * 0x504, "EASTL", 0, 0, "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    // Copy elements before insertion point from old to new.
    // FUN_00698d60 appears to be a range copy (move or construct). We'll model as memmove.
    copyConstructOrMove(&newBuf, *begin, position, newBuf, nullptr); // first param is destination, then source begin, source end, then? signature unclear.
    // Copy source element to the insertion point in new buffer.
    if (newBuf != nullptr) {
        byte* newPos = (byte*)newBuf + (int)((byte*)position - (byte*)*begin);
        for (int i = 0x141; i != 0; i--) {
            *(uint32_t*)newPos = *(uint32_t*)source;
            source = (byte*)((int)source + 4);
            newPos += 4;
        }
    }
    // Copy elements after insertion point from old to new.
    copyConstructOrMove(&newBuf, (byte*)position, currentEnd, (byte*)newBuf + 0x504, nullptr);
    // Free old buffer.
    if (*begin != 0) {
        deallocate(*begin);
    }
    // Update pointers.
    *capacity = (byte*)newBuf + newCapacity * 0x504;
    *begin = (byte*)newBuf;
    *end = (byte*)newBuf + ((int)currentEnd - (int)position) + 0x504; // old size + 1 element
}