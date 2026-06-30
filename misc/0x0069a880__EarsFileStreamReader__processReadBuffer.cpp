// FUNC_NAME: EarsFileStreamReader::processReadBuffer
// Address: 0x0069a880
// This is the finalization routine after a file has been fully read into the circular buffer.
// It parses a header (type and count), copies each packet (0x504 bytes) into the buffer,
// then closes the file handle. For non-standard packet types, it creates a new empty header.

struct PacketHeader {
    int type;                    // +0x00
    unsigned short count;        // +0x04
    unsigned short reserved;     // +0x06
}; // size = 0x08

const int PACKET_SIZE = 0x504; // 1284 bytes (321 dwords)
const int HEADER_SIZE = 0x0C;  // assumed header overhead for the data block

uint __fastcall EarsFileStreamReader::processReadBuffer(int* thisPtr)
{
    int* piVar1;
    BOOL closeResult;
    uint packetSize;
    uint* destPtr;
    int type;
    int i;
    uint* srcPtr;
    uint returnVal;
    int packetIndex;
    uint localBuffer[321]; // 0x504 bytes

    // Check if all data has been read (readPos == totalSize)
    if (thisPtr[0] == thisPtr[7]) {
        piVar1 = (int*)thisPtr[5];
        type = *piVar1;

        // If the data is not packet type 4, or the packet count is zero, set an error flag
        if ((type != 4) || (*(unsigned short*)(piVar1 + 1) == 0)) {
            thisPtr[8] = -0x10000; // error code
        }
        else {
            // Calculate per-packet size from the total data and the number of packets
            packetSize = (thisPtr[9] - HEADER_SIZE) / (uint)*(unsigned short*)(piVar1 + 1);
            thisPtr[0x0C] = thisPtr[0x0B] + 8; // offset to first packet data
            packetIndex = 0;

            if ((short)piVar1[1] != 0) {
                do {
                    // Clear the local packet buffer
                    memset(localBuffer, 0, sizeof(localBuffer));

                    // Copy the current packet from the data block
                    memcpy(localBuffer, (void*)thisPtr[0x0C], packetSize);

                    destPtr = (uint*)thisPtr[2];
                    if (destPtr < (uint*)thisPtr[3]) {
                        // There is room in the circular buffer; advance the write pointer
                        thisPtr[2] = (int)(destPtr + 321); // 321 dwords = 0x504 bytes
                        if (destPtr != nullptr) {
                            srcPtr = localBuffer;
                            for (i = 321; i != 0; i--) {
                                *destPtr = *srcPtr;
                                srcPtr++;
                                destPtr++;
                            }
                        }
                    }
                    else {
                        // Ring buffer full – use alternative handler (likely flushes or overwrites)
                        FUN_0069a140(destPtr, localBuffer);
                    }

                    thisPtr[8]++; // increment packet counter
                    thisPtr[0x0C] += packetSize;
                    packetIndex++;
                } while (packetIndex < (int)(uint)*(unsigned short*)(piVar1 + 1));
            }
        }

        // Reset the read offset
        thisPtr[0x0C] = 0;

        // Close the file handle
        closeResult = CloseHandle((void*)thisPtr[6]);
        if (closeResult == 0) {
            returnVal = 2;
        }
        else {
            thisPtr[6] = -1;
            returnVal = 8;
        }

        // For non-standard type (the error branch), allocate a new empty header and continue
        if (type != 4) {
            FUN_00699210(); // Some global cleanup or state update
            uint* newHeader = (uint*)FUN_009c8e50(8); // allocate 8 bytes for header
            if (newHeader != nullptr) {
                newHeader[0] = 4;
                *(unsigned short*)(newHeader + 1) = 0;
                *(unsigned short*)((int)newHeader + 6) = 0;
            }
            thisPtr[5] = (int)newHeader;
            int refCount = FUN_00ab8560(0, newHeader, 8);
            thisPtr[7] = refCount;
            thisPtr[0] = refCount;
        }

        return returnVal;
    }

    // If data not fully read yet, just close handle and return 7 (pending status)
    closeResult = CloseHandle((void*)thisPtr[6]);
    if (closeResult != 0) {
        thisPtr[6] = -1;
    }
    return 7;
}