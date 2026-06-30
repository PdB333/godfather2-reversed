// FUNC_NAME: WideStringBuffer::Append
int* __thiscall WideStringBuffer::Append(int* thisPtr, short* source)
{
    short* currentPos;
    short ch;
    undefined2* segmentStart;
    undefined2* segmentEnd;
    undefined2* nextSegment;

    // If the buffer's data pointer is null, nothing to do
    if (*thisPtr == 0) {
        return thisPtr;
    }

    // Get the first memory segment (or the current free pointer?) from some allocator
    segmentStart = (undefined2*)sub_4dc860();
    if (segmentStart == (undefined2*)0x0) {
        return thisPtr;
    }

    // Calculate the length of the source wide string (excluding null terminator)
    currentPos = source + 1; // point to second character
    do {
        ch = *source;
        source = source + 1;
    } while (ch != 0);
    // After loop, source points past the null terminator
    int length = (int)source - (int)currentPos >> 1; // number of characters (shorts) - 1? Actually (source - (source_original+1)) / 2 = strlen

    // Walk through the segment chain until the end
    segmentEnd = (undefined2*)sub_4dc860();
    while (segmentEnd != (undefined2*)0x0) {
        nextSegment = (undefined2*)sub_4dc860();
        segmentStart = segmentEnd;
        segmentEnd = nextSegment;
    }

    // Now segmentStart points to the last non-null segment in the chain
    // If the new string would end exactly at the current buffer end (base + count*2)
    if (segmentStart + length == (undefined2*)(*thisPtr + thisPtr[1] * 2)) {
        // Write a null terminator at the start of the segment? This seems suspicious.
        *segmentStart = 0;
        // Update the count to reflect the new position relative to the base
        thisPtr[1] = ((int)segmentStart - *thisPtr) >> 1;
    }

    return thisPtr;
}