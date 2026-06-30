// FUNC_NAME: PacketWindow::countActiveSlots
// Address: 0x00637790
// Role: Counts active slots in a packet window (send and receive) and groups them by power-of-two buckets.
// The function processes two arrays: an 8-byte entry array (send window) and a 20-byte entry array (receive window).
// It accumulates counts per bucket (0..24) and total active entries, then calls a helper to finalize.

void PacketWindow::countActiveSlots(int *outCount, int param3)
{
    int totalCount = 0;
    int currentOffset = 0;
    int chunkIndex = 0;
    int slotCounts[25] = {0}; // buckets for power-of-two groups

    // First pass: process send window entries (8-byte structures at +0x0C)
    int *bucketPtr = slotCounts;
    do {
        int chunkSize = 1 << (chunkIndex & 0x1f);
        int maxEntries = *(int *)(this + 0x1C); // total number of send entries

        if (maxEntries < chunkSize) {
            chunkSize = maxEntries;
            if (maxEntries <= currentOffset) {
                // Zero remaining buckets
                if (chunkIndex < 0x19) {
                    int *clearPtr = slotCounts + chunkIndex;
                    for (int i = 0x19 - chunkIndex; i != 0; i--) {
                        *clearPtr = 0;
                        clearPtr++;
                    }
                }
                break;
            }
        }

        *bucketPtr = 0;
        if (currentOffset < chunkSize) {
            int entriesToProcess = chunkSize - currentOffset;
            int *entryPtr = (int *)(*(int *)(this + 0x0C) + currentOffset * 8);
            currentOffset += entriesToProcess;
            do {
                if (*entryPtr != 0) {
                    *bucketPtr = *bucketPtr + 1;
                    totalCount++;
                }
                entryPtr += 2; // skip second int of 8-byte structure
                entriesToProcess--;
            } while (entriesToProcess != 0);
        }
        chunkIndex++;
        bucketPtr++;
    } while (chunkIndex < 0x19);

    // Second pass: process receive window entries (20-byte structures at +0x10)
    int numEntries = 1 << (*(byte *)(this + 7) & 0x1f); // number of receive entries (power of two)
    if (numEntries != 0) {
        int *entryPtr = (int *)(*(int *)(this + 0x10) + numEntries * 0x14);
        do {
            numEntries--;
            entryPtr -= 5; // move back 5 ints (20 bytes)
            if (entryPtr[2] != 0) { // active flag at offset +8 (third int)
                // Check type == 3 and sequence number is a positive integer
                if (entryPtr[0] == 3) { // type field at offset 0
                    int seq = (int)(float)entryPtr[1]; // sequence number stored as float
                    if ((float)seq == (float)entryPtr[1] && seq > 0) {
                        // Compute bucket index from sequence number (highest set bit position)
                        unsigned int bucketIndex;
                        unsigned int uSeq = seq - 1;
                        if (uSeq < 0x10000) {
                            if (uSeq < 0x100) {
                                if (uSeq == 0) {
                                    bucketIndex = 0xFFFFFFFF;
                                } else {
                                    bucketIndex = (unsigned int)*(byte *)((int)&bitScanTable + (uSeq & 0xff));
                                }
                            } else {
                                bucketIndex = *(byte *)((int)&bitScanTable + ((uSeq >> 8) & 0xff)) + 8;
                            }
                        } else if (uSeq < 0x1000000) {
                            bucketIndex = *(byte *)((int)&bitScanTable + ((uSeq >> 16) & 0xff)) + 16;
                        } else {
                            bucketIndex = *(byte *)((int)&bitScanTable + (uSeq >> 24)) + 24;
                        }
                        slotCounts[bucketIndex + 1]++;
                        totalCount++;
                    }
                }
            }
        } while (numEntries != 0);
    }

    // Call helper to finalize counts
    FUN_00637710(totalCount, outCount, param3);
}