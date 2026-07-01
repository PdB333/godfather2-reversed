// FUNC_NAME: TNLConnection::processIncomingPacketStream
int TNLConnection::processIncomingPacketStream(int *thisPtr, uint *buffer, int size)
{
    int totalProcessed = 0;
    // Get the network/packet manager (singleton)
    void *pManager = getPacketManager();
    // Lock the connection's receive mutex at offset 0x6E
    lockMutex((int *)thisPtr + 0x6E);
    
    if (0 < size) {
        do {
            // Check the command byte at offset 6 of the current packet header
            // (buffer[1] low byte at byte offset 6)
            if (*(char *)((int)buffer + 6) == 0x02) {
                // Special command packet; call virtual handler at vtable+0x1C
                (*(code **)(*thisPtr + 0x1C))(*thisPtr); // this->handleCommandPacket()
            } else {
                // Normal packet: check if packet manager can accept more
                int avail = checkPacketAvailable(pManager);
                if (avail < 1) break; // No room; stop processing
            }
            // Calculate the aligned chunk size from the packet's second uint
            // Low 16 bits contain the raw packet size, add 17 bytes of overhead, then align to 4 (mask 0x7FFC)
            uint chunkSize = ((ushort)buffer[1] + 0x17) & 0x7FFC;
            totalProcessed += chunkSize;
            // Write the aligned chunk size back into the first uint (for caller to advance)
            *buffer = chunkSize;
            if (size == 1) break;
            size -= chunkSize;
            buffer = (uint *)((int)buffer + chunkSize);
        } while (0 < size);
    }
    // If flush flag at offset 0x77 (0x1DC) is set, flush pending data
    if (0 < thisPtr[0x77]) {
        processPendingFlush();
    }
    // Unlock mutex
    unlockMutex((int *)thisPtr + 0x6E);
    return totalProcessed;
}