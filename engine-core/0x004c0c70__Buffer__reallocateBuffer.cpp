// FUNC_NAME: Buffer::reallocateBuffer
// Address: 0x004c0c70
// Role: Reallocates internal buffer to a new capacity, copying old data and zeroing extra bytes.
// Structure offsets used:
//   +0x14: Allocator function pointer (takes size and allocInfo struct, returns new buffer)
//   +0x18: Current buffer size (uint)
//   +0x1c: Current buffer data pointer (void*)

void* __fastcall Buffer::reallocateBuffer(uint* outOldSize, uint* outNewSize, void* thisBuffer, uint newCapacity)
{
    uint currentSize;
    uint allocatedSize;
    void* newBuffer;
    uint allocInfo[3]; // Allocation info structure (3 dwords, zeroed)

    // Capture original size
    currentSize = *(uint*)((uint)thisBuffer + 0x18);
    *outOldSize = currentSize;

    // Determine new allocated size: max of current size and requested capacity
    if (newCapacity < currentSize)
        allocatedSize = currentSize;
    else
        allocatedSize = newCapacity;
    *outNewSize = allocatedSize;

    // Allocate if size > 0 and allocator is present
    if (allocatedSize != 0 && *(int*)((uint)thisBuffer + 0x14) != 0)
    {
        // Zero out the allocation info structure
        allocInfo[0] = 0;
        allocInfo[1] = 0;
        allocInfo[2] = 0;

        // Call allocator function pointer at +0x14
        // This function likely has signature: void* allocate(uint size, uint* allocInfo)
        newBuffer = (void*)(*(uint (__fastcall**)(uint, uint*))(*(uint*)((uint)thisBuffer + 0x14)))(allocatedSize, allocInfo);

        if (newBuffer != nullptr)
        {
            // Copy existing data into new buffer
            memcpy(newBuffer, *(void**)((uint)thisBuffer + 0x1c), currentSize);

            // Zero the extra space if new capacity exceeds original size
            if (currentSize < newCapacity)
            {
                memset((void*)((uint)newBuffer + currentSize), 0, newCapacity - currentSize);
            }
        }
    }
    else
    {
        newBuffer = nullptr;
    }

    return newBuffer;
}