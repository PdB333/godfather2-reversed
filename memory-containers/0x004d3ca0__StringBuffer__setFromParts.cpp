// FUNC_NAME: StringBuffer::setFromParts
// Function at 0x004d3ca0
// Constructs or resets a string buffer from up to two data parts.
// Structure fields:
//   +0x00: char* mBuffer
//   +0x04: int mLength
//   +0x08: int mCapacity
//   +0x0C: void (*mDeallocator)(void*)

void __thiscall StringBuffer::setFromParts(int* thisPtr, void* part1Data, size_t part1Size, void* part2Data, size_t part2Size)
{
    void* newBuffer;
    int totalSize;

    if (part1Size == 0)
    {
        if (part2Size != 0)
        {
            // Only second part provided
            thisPtr[1] = part2Size;   // mLength = part2Size
            thisPtr[2] = part2Size;   // mCapacity = part2Size
            newBuffer = allocateMemory(part2Size + 1); // +1 for null terminator
            thisPtr[0] = (int)newBuffer;
            thisPtr[3] = (int)deallocateMemory; // set deallocator function
            memcpy(newBuffer, part2Data, part2Size);
            *(char*)(thisPtr[1] + thisPtr[0]) = 0; // null-terminate at buffer[length]
            return;
        }
        // Both empty: clear buffer
        thisPtr[0] = 0;
        thisPtr[2] = 0;
        thisPtr[1] = 0;
        return;
    }

    if (part2Size != 0)
    {
        // Both parts provided: concatenate
        totalSize = part1Size + part2Size;
        thisPtr[1] = totalSize;
        thisPtr[2] = totalSize;
        newBuffer = allocateMemory(totalSize + 1);
        thisPtr[0] = (int)newBuffer;
        thisPtr[3] = (int)deallocateMemory;
        memcpy(newBuffer, part1Data, part1Size);
        memcpy((void*)(thisPtr[0] + part1Size), part2Data, part2Size);
        *(char*)(thisPtr[1] + thisPtr[0]) = 0;
        return;
    }

    // Only first part provided (no second part)
    thisPtr[1] = part1Size;
    thisPtr[2] = part1Size;
    newBuffer = allocateMemory(part1Size + 1);
    thisPtr[0] = (int)newBuffer;
    thisPtr[3] = (int)deallocateMemory;
    memcpy(newBuffer, part1Data, part1Size);
    *(char*)(thisPtr[1] + thisPtr[0]) = 0;
    return;
}