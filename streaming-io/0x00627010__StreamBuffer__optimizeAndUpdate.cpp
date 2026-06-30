// FUNC_NAME: StreamBuffer::optimizeAndUpdate

void __thiscall StreamBuffer::optimizeAndUpdate(int param_1)
{
    // this is in ECX
    int* internalBuffer = *(int**)(this + 0x10);  // pointer to internal structure at offset 0x10
    int size             = *(int*)(internalBuffer + 0x4);  // +0x04: number of used entries
    int capacity         = *(int*)(internalBuffer + 0x8);  // +0x08: total capacity

    // Check if usage is low relative to capacity and capacity is large enough
    // (capacity + (capacity >> 31 & 3)) >> 2  =>  capacity / 4  (with rounding for negative)
    int quarterCap = (capacity + (capacity >> 31 & 3)) >> 2;
    if (size < quarterCap && capacity > 0x40)
    {
        internalGrowOrCompact();  // Likely compacts or reallocates the buffer
    }

    int count = *(int*)(internalBuffer + 0x1c);  // +0x1c: another counter (e.g., allocation count)
    if (count > 0x40)
    {
        int newCount = count >> 1;  // Halve the count
        void* newBuffer = reallocHalf(count, newCount);  // Reallocate to half size
        *(void**)(internalBuffer + 0x18) = newBuffer;  // +0x18: store new pointer
        *(int*)(internalBuffer + 0x1c) = newCount;     // Update count
    }

    // Update a "last update" or "frame index" value
    // Formula: newValue = (oldValue * 2) - currentFrame?
    int oldValue = *(int*)(internalBuffer + 0x24);  // +0x24: previous timestamp or value
    *(int*)(internalBuffer + 0x20) = oldValue * 2 - param_1;
}