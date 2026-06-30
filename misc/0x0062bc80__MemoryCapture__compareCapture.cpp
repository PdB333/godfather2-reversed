// FUNC_NAME: MemoryCapture::compareCapture
// Function at 0x0062bc80: Compares a buffer against a stored memory capture at given index.
// Returns pointer to end of buffer if match, 0 on mismatch or out-of-range.
// Object structure:
// +0x04: capacity (end pointer of buffer region)
// +0x0C: captureCount (number of entries)
// +0x10: capture entries array (each entry: 4 bytes pointer, 4 bytes size)

byte* __fastcall MemoryCapture::compareCapture(void* thisPtr, int captureIndex, byte* bufferPointer)
{
    uint captureSize;
    int cmpResult;
    byte* capturePtr;
    byte* currentBufferPos;
    uint remaining;
    int diff;

    captureIndex -= 0x31; // adjust index (maybe enum offset)

    // Validate capture index
    if (captureIndex < 0 || captureIndex >= *(int*)((byte*)thisPtr + 0xC) ||
        (captureSize = *(uint*)((byte*)thisPtr + 0x14 + captureIndex * 8), captureSize == 0xFFFFFFFF))
    {
        errorMessage("invalid capture index"); // 0x00627bd0
        __debugbreak(); // swi(3)
        return (byte*)(*((code**)0))(); // unconventional, but matches decompiled
    }

    // Check if buffer can accommodate the capture size
    if ((uint)(*(int*)((byte*)thisPtr + 4) - (int)bufferPointer) < captureSize)
        return 0;

    capturePtr = *(byte**)((byte*)thisPtr + 0x10 + captureIndex * 8);
    currentBufferPos = bufferPointer;
    remaining = captureSize;

    // Compare 4 bytes at a time while possible
    for (; 3 < remaining; remaining -= 4)
    {
        if (*(int*)capturePtr != *(int*)currentBufferPos)
            goto compareRemaining;
        currentBufferPos += 4;
        capturePtr += 4;
    }

    // Compare remaining bytes (0-3)
    if (remaining == 0)
        return bufferPointer + captureSize; // exact match

compareRemaining:
    // Perform byte-by-byte diff
    diff = (int)*capturePtr - (int)*currentBufferPos;
    if (diff == 0)
    {
        if (remaining == 1)
            return bufferPointer + captureSize;
        diff = (int)capturePtr[1] - (int)currentBufferPos[1];
        if (diff == 0)
        {
            if (remaining == 2)
                return bufferPointer + captureSize;
            diff = (int)capturePtr[2] - (int)currentBufferPos[2];
            if (diff == 0)
            {
                if (remaining == 3 || (diff = (int)capturePtr[3] - (int)currentBufferPos[3], diff == 0))
                    return bufferPointer + captureSize;
            }
        }
    }

    // Mismatch
    return 0;
}