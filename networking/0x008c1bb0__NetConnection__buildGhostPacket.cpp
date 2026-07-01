// FUNC_NAME: NetConnection::buildGhostPacket
// Function address: 0x008c1bb0
// Role: Packs a list of ghost updates into a buffer for network transmission.
// Each update is 0x1c bytes in memory, serialized into a 16-byte header plus variable-length data.
// The array pointer is at this+0x130, count at this+0x134.
// Returns total size of the packed buffer (including header and variable data).

int __thiscall NetConnection::buildGhostPacket(int thisPtr, int outBuffer) {
    int count = *(int *)(thisPtr + 0x134); // Number of ghost updates
    int totalSize = 0;
    int sumSizes = 0;

    // First pass: sum the size fields (offset 0x14) of each update
    if (count != 0) {
        int *sizePtr = (int *)(*(int *)(thisPtr + 0x130) + 0x14); // Point to first element's size field
        int remaining = count;
        do {
            totalSize += *sizePtr;
            sizePtr += 7; // Advance by 7 ints (0x1c bytes) to next element's size field
            remaining--;
            sumSizes = totalSize;
        } while (remaining != 0);
    }

    // Current write position in output buffer (starts after the fixed-size header for all updates)
    int writePos = count * 0x10 + outBuffer;

    // Second pass: serialize each update
    if (count != 0) {
        int *outPtr = (int *)(outBuffer + 4); // Output pointer for the 16-byte header (starts at offset 4? Actually writes to -1,0,1,2 relative to this)
        int inputOffset = 0; // Byte offset into the input array
        int remaining = count;
        do {
            int *inputElem = (int *)(*(int *)(thisPtr + 0x130) + inputOffset); // Base of current update element

            // Write first int: value from offset 0x04 of the element
            outPtr[-1] = *(int *)(*(int *)(thisPtr + 0x130) + 4 + inputOffset);

            // Write second int: byte flag from offset 0x0c (zero-extended)
            outPtr[1] = (uint)*(byte *)((int)inputElem + 0xc);

            // Write third int: if pointer at offset 0x08 is non-null, read value at +0x38 from that object; else 0
            if (*(int *)((int)inputElem + 8) == 0) {
                outPtr[0] = 0;
            } else {
                outPtr[0] = *(int *)(*(int *)((int)inputElem + 8) + 0x38);
            }

            // Write fourth int: value from offset 0x14 (size field)
            outPtr[2] = *(int *)((int)inputElem + 0x14);

            // Pack variable-length data starting at offset 0x10 of the element
            int written = FUN_008bfc50(writePos, (int)inputElem + 0x10);
            writePos += written;

            // Advance output pointer by 4 ints (16 bytes)
            outPtr += 4;
            // Advance input offset by element size (0x1c bytes)
            inputOffset += 0x1c;
            remaining--;
        } while (remaining != 0);
    }

    // Total size = (sum of size fields + count) * 16
    return (sumSizes + count) * 0x10;
}