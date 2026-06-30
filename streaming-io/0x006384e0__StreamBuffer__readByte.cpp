// FUNC_NAME: StreamBuffer::readByte
// Function at 0x006384e0 - reads next byte from a buffer, returns byte or -1 on failure.
// Class likely has fields: remainingCount (int) at +0x00, currentPtr (byte*) at +0x04,
// getDataFunc (function pointer) at +0x08, sourceParam (int) at +0x0C.
// getDataFunc signature: (int arg0, int srcParam, int* outSize) -> byte*
uint StreamBuffer::readByte(void)
{
    byte* dataPtr;
    int dataSize;
    
    // Call the user-supplied function to get a pointer to raw data.
    // arg0 is 0, this->getDataFunc is stored at +0x08, this->sourceParam at +0x0C.
    dataPtr = (byte*)(this->getDataFunc)(0, this->sourceParam, &dataSize);
    if ((dataPtr != (byte*)0x0) && (dataSize != 0)) {
        // Set the current read pointer to the beginning of data.
        this->currentPtr = dataPtr;
        // Remaining bytes = dataSize - 1 (since we will consume one).
        this->remainingCount = dataSize - 1;
        // Read the first byte.
        byte result = *dataPtr;
        // Advance the read pointer past the byte.
        this->currentPtr = dataPtr + 1;
        return (uint)result;
    }
    // Return -1 to indicate failure or EOF.
    return 0xffffffff;
}