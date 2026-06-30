// FUNC_NAME: BufferedStreamReader::peekByte

uint __thiscall BufferedStreamReader::peekByte(void)
{
    byte* newBuffer;
    int bytesRead;
    byte firstByte;
    
    // Fast path: if buffer has bytes, return current byte without advancing
    if (this->remainingBytes != 0) {
        return (uint)*(this->bufferPtr);
    }
    
    // Buffer empty: refill using the registered callback
    // Callback signature: (int arg0, int streamContext, int* outBytesRead) -> byte*
    newBuffer = (byte*)(this->readCallback)(0, this->streamContext, &bytesRead);
    
    if ((newBuffer != nullptr) && (bytesRead != 0)) {
        // Initialize buffer state: point to new buffer, set remaining to bytesRead-1
        this->bufferPtr = newBuffer;
        this->remainingBytes = bytesRead - 1;
        
        // Read the first byte of the new buffer
        firstByte = *newBuffer;
        this->bufferPtr = newBuffer + 1;  // advance past it
        
        // If first byte is not 0xFF (EOF sentinel), revert the consumption
        // and let the fast path return it as a normal byte
        if (firstByte != (byte)0xFF) {
            this->remainingBytes = bytesRead;
            this->bufferPtr = newBuffer;
            goto LAB_FAST_PATH; // Actually just return the byte via fast path
        }
        // If first byte is 0xFF, it's an EOF marker; it's been consumed
        // (bufferPtr already advanced, remainingBytes = bytesRead-1)
        // Return 0xFFFFFFFF to indicate end of stream
    }
    
    // No data or error, return EOF
    return 0xFFFFFFFF;
    
LAB_FAST_PATH:
    return (uint)*(this->bufferPtr);
}