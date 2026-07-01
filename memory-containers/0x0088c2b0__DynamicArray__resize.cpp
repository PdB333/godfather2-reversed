// FUNC_NAME: DynamicArray::resize
void __thiscall DynamicArray::resize(uint newSize)
{
    // this points to structure with:
    // +0x00: int* start (beginning of allocated buffer)
    // +0x04: int* end   (one past last used element)

    int* src = this->end;                  // current end pointer
    uint currentSize = (src - this->start); // number of ints currently stored

    if (currentSize < newSize)
    {
        // Not enough space: grow the array
        int extraElements = newSize - currentSize;
        uint newCapacity = 0;
        // FUN_0088b690 – allocates additional memory, updates end pointer
        Grow(this->end, extraElements, &newCapacity);
        return;
    }

    // Shrink: just move the end pointer back
    int* dst = this->start + newSize;       // new end pointer
    // Note: memmove with size 0 is a no‑op, kept to match decompilation
    _memmove(dst, src, 0);
    this->end = this->end + ((src - dst) / 4) * -4; // adjusts to dst
}