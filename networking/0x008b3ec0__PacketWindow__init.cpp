// FUNC_NAME: PacketWindow::init
// Function address: 0x008b3ec0
// This function initializes a packet window structure with two arrays (send/receive or sequence buffers).
// The structure is part of the TNL networking layer, likely managing a sliding window of sequence numbers.

void __thiscall PacketWindow::init(int *this, uint windowSize, int startSequence)
{
    long long lVar1;
    int *internalBuffer;
    undefined4 uVar3;
    uint i;

    this[3] = startSequence;                        // +0x0C: starting sequence number
    this[1] = 0;                                    // +0x04: some counter (e.g., oldest pending ack)
    this[2] = windowSize;                           // +0x08: window capacity (e.g., 32)
    this[4] = 0;                                    // +0x10: flags or next expected

    internalBuffer = (int *)FUN_009c8e50(0x18);     // allocate internal structure (size 24 bytes)
    if (internalBuffer != (int *)0) {
        lVar1 = (ulonglong)(windowSize + 1) * 4;    // size of array (uint32 per slot)
        internalBuffer[1] = 0;                      // +0x04: clear first field
        uVar3 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
        internalBuffer[5] = (int)uVar3;             // +0x14: pointer to packet state array
    }
    *this = (int)internalBuffer;                    // +0x00: pointer to internal structure

    // Zero out the packet state array (windowSize+1 entries)
    i = 0;
    do {
        *(undefined4 *)(internalBuffer[5] + i * 4) = 0;
        i = i + 1;
    } while (i <= windowSize);

    // Allocate a second array of the same size (maybe for matching outgoing/incoming)
    lVar1 = (ulonglong)(windowSize + 1) * 4;
    this[5] = (int)FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // +0x14: second array pointer
    return;
}

// Note: FUN_009c8e50 and FUN_009c8e80 are likely memory allocators (malloc and calloc respectively).
// The internal structure layout:
//   *this[0] -> internalBuffer (0x18 bytes)
//       internalBuffer[0]: (unused? could be flags or link)
//       internalBuffer[1]: +0x04 -> counter/flag
//       internalBuffer[5]: +0x14 -> pointer to packet state array (uint32[windowSize+1])
//   this[1]: +0x04 -> oldest pending ack
//   this[2]: +0x08 -> window size
//   this[3]: +0x0C -> start sequence
//   this[4]: +0x10 -> next expected sequence (or flags)
//   this[5]: +0x14 -> pointer to second array (e.g., send flags or receive flags)