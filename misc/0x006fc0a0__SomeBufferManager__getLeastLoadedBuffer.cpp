// FUNC_NAME: SomeBufferManager::getLeastLoadedBuffer
void __thiscall SomeBufferManager::getLeastLoadedBuffer(int *outBufferPtr, int *outIndex)
{
    // +0x1a0: unsigned int countA (number of items in buffer at +0x180)
    // +0x1d8: unsigned int countB (number of items in buffer at +0x1b8)
    unsigned int countA = *(unsigned int *)(this + 0x1a0);
    unsigned int countB = *(unsigned int *)(this + 0x1d8);

    if (countA < countB)
    {
        // +0x180: bufferA (e.g., an array of entries)
        *outBufferPtr = (int)(this + 0x180);
        *outIndex = 0;
        return;
    }
    if (countB < countA)
    {
        // +0x1b8: bufferB
        *outBufferPtr = (int)(this + 0x1b8);
        *outIndex = 1;
    }
    // If counts are equal, output parameters are left unchanged (caller must handle)
}