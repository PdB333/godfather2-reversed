// FUNC_NAME: NetworkBuffer::initialize
// Address: 0x0066a970
// Role: Initializes a network buffer for packet building. Allocates internal memory,  
// writes data from the internal buffer to an output buffer, and cleans up.

int NetworkBuffer::initialize(char* outBuffer)
{
    // Allocate internal buffer: 4 blocks of 64 bytes each (256 bytes total)
    char* internalBuffer = (char*)_calloc(4, 0x40);
    if (!internalBuffer) {
        return -2;  // Allocation failure
    }

    int offset = 0;            // Current write offset in output buffer
    int bufferSize = 0x40;     // Size of each internal block (possibly max write size)
    int bytesWritten = 0;      // Accumulated bytes written

    // Begin packet building sequence
    int result = startPacketWrite();  // FUN_00665ce0
    if (result != 0) {
        return result;
    }

    // Process data: copy from internal buffer to output buffer
    do {
        // Copy one byte from internal buffer to output buffer
        outBuffer[offset] = internalBuffer[0]; // Note: would normally copy sequential bytes
        offset++;

        // Attempt to read next chunk (8 bytes) into the offset variable
        result = readNextChunk(&offset, 8, &offset, 0); // FUN_00666300
        if (result != 0) {
            cleanupBuffer();   // FUN_00665b40
            return result;
        }
    } while (offset != 0);  // Continue until offset is zero (end of data)

    finalizePacket();   // FUN_0066bb10
    cleanupBuffer();    // FUN_00665b40

    return 0;  // Success
}