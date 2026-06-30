// FUNC_NAME: StreamReader::readByte
// Role: Reads one byte from a network/stream buffer, refilling if necessary.
// Returns the byte as uint, or 0xFFFFFFFF on error/eof.
// The stream buffer structure at this+0x04:
//   +0x00: remainingCount (int) – number of bytes left in current buffer chunk
//   +0x04: currentPointer (byte*) – next byte to read
//   +0x08: refillFunc (void*)(*)(uint, void*, int*) – refill callback
//   +0x0C: refillContext (void*) – opaque parameter for callback

uint StreamReader::readByte()
{
    // Get the stream buffer pointer (at this+0x04)
    int *pStreamBuf = *(int **)(this + 4);

    // Decrement remaining count and check if we need to refill
    int oldCount = *pStreamBuf;
    *pStreamBuf = oldCount - 1;

    uint result;

    if (oldCount == 0)
    {
        // Buffer exhausted – call refill function
        // refillFunc is at pStreamBuf[2], context at pStreamBuf[3]
        int newSize;
        byte *newBuf = (byte *)(*(code *)pStreamBuf[2])(0, pStreamBuf[3], &newSize);

        if (newBuf == nullptr || newSize == 0)
        {
            result = 0xFFFFFFFF; // EOF or error
        }
        else
        {
            // Set up the new buffer: pointer at pStreamBuf[1], count = newSize-1 (one byte will be read now)
            pStreamBuf[1] = (int)newBuf;
            *pStreamBuf = newSize - 1;

            // Read the first byte from new buffer
            result = (uint)*newBuf;
            pStreamBuf[1] = (int)(newBuf + 1); // advance pointer
        }
    }
    else
    {
        // Buffer has data – read byte directly
        byte *curPtr = *(byte **)(pStreamBuf + 1); // pStreamBuf[1] is current pointer
        result = (uint)*curPtr;
        *(byte **)(pStreamBuf + 1) = curPtr + 1; // advance
    }

    // If result is the error/EOF marker, delegate to error handler
    if (result == 0xFFFFFFFF)
    {
        return FUN_00641890(); // likely returns 0xFFFFFFFF or actual error code
    }

    return result;
}