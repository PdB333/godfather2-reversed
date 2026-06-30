// FUNC_NAME: StreamBuffer::read
// Function address: 0x00701ff0
// Reconstructed from Ghidra decompilation. This function reads data from a ring buffer or stream,
// with handling for wrapping and secondary reads after flush.
// Offsets:
// +0x2d0: pointer to underlying stream? (checked for non-null)
// +0x334: handle or pointer to data source
// +0x2d8: flags (bit 2: allow secondary read after flush)
// +0x214: enum or type constant (checked against 0x48)
// +0x161: boolean flag (enables secondary read path)

uint __thiscall StreamBuffer::read(uint bytesToRead)
{
    uint totalBytesRead = 0;
    
    if (*(int*)(this + 0x2D0) != 0) {
        // Get available bytes in current contiguous segment
        uint available = getAvailable(*(void**)(this + 0x334));
        uint bufferSizeOrPos = getBufferSizeOrWritePos(); // Possibly total buffer size or write index
        
        if (available < bufferSizeOrPos) {
            // We have data in a linear region (no wrap)
            uint bytesToConsume = bufferSizeOrPos - available; // Remaining in segment?
            if (bytesToConsume > bytesToRead) {
                bytesToConsume = bytesToRead;
            }
            
            // Advance the read pointer by bytesToConsume
            advanceReadPointer(*(void**)(this + 0x334), bytesToConsume);
            totalBytesRead = bytesToConsume;
            
            // Check if secondary read is allowed
            if (((*(uint*)(this + 0x2D8) >> 2 & 1) != 0) &&          // Allow secondary?
                (*(int*)(this + 0x214) != 0) &&                      // Type check
                (*(int*)(this + 0x214) != 0x48) &&                   // Not specific type
                (*(char*)(this + 0x161) != '\0'))                    // Flag enabled
            {
                flushPendingData(); // Possibly process pending data
                
                if (totalBytesRead < bytesToRead) {
                    // Try to read more from the next segment
                    uint secondaryAvailable = getAvailable(*(void**)(this + 0x334));
                    uint secondaryPos = getBufferSizeOrWritePos();
                    uint remainingCapacity = secondaryPos - secondaryAvailable;
                    
                    if (remainingCapacity != 0) {
                        uint bytesFromSecondary = bytesToRead - totalBytesRead;
                        if (bytesFromSecondary > remainingCapacity) {
                            bytesFromSecondary = remainingCapacity;
                        }
                        
                        advanceReadPointer(*(void**)(this + 0x334), bytesFromSecondary);
                        totalBytesRead += bytesFromSecondary;
                    }
                }
            }
        }
        else {
            // Wrap-around case: available >= bufferSize? Reset or seek
            uint writePos = getBufferSizeOrWritePos();
            if (writePos < available) {
                uint newPos = getBufferSizeOrWritePos();
                setPosition(*(void**)(this + 0x334), newPos);
            }
        }
    }
    
    return totalBytesRead;
}