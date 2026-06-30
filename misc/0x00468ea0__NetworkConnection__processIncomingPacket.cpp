// FUNC_NAME: NetworkConnection::processIncomingPacket

// Reconstructed C++ for function at 0x00468ea0
// This function appears to process an incoming network packet (type 6) from the engine's internal buffer manager.
// It uses a global engine context pointer (g_engineContext at 0x012233f4) to obtain the buffer manager.
// The 'this' pointer is passed in EAX (custom calling convention); here it is mapped to 'this' for readability.

void NetworkConnection::processIncomingPacket(int param_1)
{
    if (this == 0) {
        return;
    }

    // Dereference global engine context to get pointer to buffer manager
    // g_engineContext is a global pointer; offset 0x18 yields the buffer manager address
    int* bufferManager = *(int**)((char*)g_engineContext + 0x18);

    // Lock the buffer manager for exclusive access (likely a mutex/semaphore wrapper)
    lockBuffer(bufferManager);

    // Reserve 8 bytes at the current end of the buffer
    // bufferManager+0x40 is the write cursor; the size is bufferManager[2] (offset 0x08) - 8
    int currentSize = *(int*)(bufferManager + 2);  // offset 0x08: current buffer size
    int reserveSize = currentSize - 8;
    undefined4* reservedSpace = reserveBufferSpace(bufferManager, bufferManager + 0x40, reserveSize, 0);

    // Write the reserved 8 bytes (likely packet header) from the caller's data
    int* writePos = (int*)(*(int*)(bufferManager + 2) - 8);  // offset 0x08: buffer end
    *(undefined4*)(writePos + 0) = reservedSpace[0];
    *(undefined4*)(writePos + 1) = reservedSpace[1];

    // Interpret the first dword as a packet type identifier
    int* packetHeader = (int*)(*(int*)(bufferManager + 2) - 8);
    if (packetHeader != 0 && *packetHeader == 6) {
        // Packet type 6: process the payload
        processPacketData(param_1);

        // Compute remaining buffer size after consuming current data
        // unaff_EDI (from register) represents a count of consumed elements (each 8 bytes)
        int consumedBytes = unaff_EDI * 8 + 8;  // assume unaff_EDI is an index
        int remainingOffset[2];
        remainingOffset[0] = *(int*)(bufferManager + 2) - consumedBytes;  // offset 0x08: new buffer position
        remainingOffset[1] = 0;

        // Copy remaining data or update stream pointer using a global stream label
        // g_packetStream is a global memory buffer descriptor
        bufferRead(&g_packetStream, remainingOffset, remainingOffset[0] - *(int*)(bufferManager + 7));  // offset 0x1C: consumed marker
    }

    // No explicit cleanup; assumes buffer manager handles deallocation
}