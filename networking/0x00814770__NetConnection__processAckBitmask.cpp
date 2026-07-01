// FUNC_NAME: NetConnection::processAckBitmask
bool __thiscall NetConnection::processAckBitmask(uint *buffer, uint bufferSize) {
    ushort bitMask;
    ushort combinedMask;
    uint *entryPtr;
    
    if ((3 < bufferSize) && (buffer != NULL)) {
        // Acquire synchronization lock (might be mutex or critical section)
        lockMutex();
        
        // Validate buffer size: header (4 bytes) + numEntries * 8 bytes
        if (bufferSize == *buffer * 8 + 4) {
            entryPtr = buffer + 1; // Skip count header
            uint entryIndex = 0;
            uint numEntries = *buffer;
            if (numEntries != 0) {
                do {
                    // Combine low and high masks into one 16-bit set for iteration
                    combinedMask = (ushort)entryPtr[1] | *(ushort *)((int)entryPtr + 6);
                    while (combinedMask != 0) {
                        // Isolate lowest set bit
                        bitMask = -combinedMask & combinedMask;
                        
                        // Check if bit is set in low mask (bits 0-15)
                        if (((ushort)entryPtr[1] & bitMask) != 0) {
                            handleAckForBit(bitMask, *entryPtr, 1, 1); // Low half, action=1
                        }
                        // Check if bit is set in high mask (bits 16-31)
                        if ((*(ushort *)((int)entryPtr + 6) & bitMask) != 0) {
                            handleAckForBit(bitMask, *entryPtr, 0, 1); // High half, action=1
                        }
                        // Clear the processed bit
                        combinedMask &= ~bitMask;
                    }
                    entryIndex++;
                    entryPtr += 2; // Advance to next entry (8 bytes)
                } while (entryIndex < numEntries);
            }
        }
    }
    return true;
}