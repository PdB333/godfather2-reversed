// FUNC_NAME: NetConnection::computePacketWindowDistribution
// Function at 0x00637790 - Computes histogram of packet window slot occupancy and ghost packet sizes
// Called from 0x00637d60 (likely another NetConnection method)
// Uses two internal arrays: one at this+0x0c (stride 8 bytes) and one at this+0x10 (stride 0x14 bytes)
// The first array tracks active slots (non-zero first int indicates occupied)
// The second array stores ghost packets (type, float value, flags)
// Outputs total count and passes to finalizeDistribution (FUN_00637710)

#include <cstdint>

// Forward declaration
void finalizeDistribution(int totalCount, int* pOutCount, int param3);

class NetConnection {
public:
    // Fields identified by offsets (Xbox debug build)
    // +0x00: vtable
    // +0x07: uint8_t secondArraySizeLog2; // size of second array = 1 << (value & 0x1f)
    // +0x0c: int* pSlotArray; // array of 8-byte entries
    // +0x10: GhostPacket* pGhostArray; // array of 20-byte entries (GhostPacket structure)
    // +0x1c: int32_t totalSlotCount; // number of slots in first array
    // (other fields exist but irrelevant here)

    struct GhostPacket {
        int32_t type;        // -5*4 offset from end
        float   value;       // -4*4 offset from end (cast to int)
        int32_t flags;       // -3*4 offset from end (non-zero indicates activity)
        // +0x0c and +0x10: other fields (unused here)
    };

    void computePacketWindowDistribution(int* pOutCount, int param3);
};

// Bit-scan table (log2 for numbers up to 0xFFFF)
static const uint8_t bitScanTable[256] = {
    // Values from PTR_DAT_00e4218f (assumed existing in binary)
    // This table gives the position of the highest set bit in each byte (0-255)
    // For full definition, see original EA code; placeholder:
    0x00, 0x01, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    // ... (256 entries)
};

void NetConnection::computePacketWindowDistribution(int* pOutCount, int param3) {
    int histogram[32] = {0}; // actually at least 32 entries (indices 0..31)
    int totalNonZero = 0;
    int processedSlots = 0; // iVar7
    int* histPtr = histogram; // piVar5

    // First pass: process slot array (stride 8) in power-of-two chunks
    for (int chunkExp = 0; chunkExp < 25; chunkExp++) {
        int chunkSize = 1 << (chunkExp & 0x1f); // 1,2,4,...,2^24
        int remainingSlots = totalSlotCount;

        if (remainingSlots < chunkSize) {
            chunkSize = remainingSlots;
            if (remainingSlots <= processedSlots) {
                // Zero out remaining histogram entries
                for (int i = chunkExp; i < 25; i++) {
                    histogram[i] = 0;
                }
                break;
            }
        }

        *histPtr = 0;

        if (processedSlots < chunkSize) {
            int countThisChunk = chunkSize - processedSlots;
            int* slotEntry = (int*)((int)pSlotArray + processedSlots * 8); // each slot: 8 bytes, first int is presence
            processedSlots += countThisChunk;

            do {
                if (*slotEntry != 0) {
                    (*histPtr)++;
                    totalNonZero++;
                }
                slotEntry += 2; // advance 8 bytes
                countThisChunk--;
            } while (countThisChunk != 0);
        }

        histPtr++;
    }

    // Second pass: process ghost packet array (stride 0x14 = 20 bytes) in reverse
    int ghostCount = 1 << (*(uint8_t*)((int)this + 7) & 0x1f); // number of ghost packet slots
    GhostPacket* pGhost = (GhostPacket*)((int)pGhostArray + ghostCount * 0x14); // point past last element

    while (ghostCount != 0) {
        ghostCount--;

        // Move to previous element (each GhostPacket is 5 ints = 0x14 bytes)
        pGhost = (GhostPacket*)((int)pGhost - 0x14);

        if (pGhost->flags == 0) {
            continue;
        }

        if (pGhost->type == 3) {
            // For type 3 packets, extract level from value field
            int valueInt = (int)pGhost->value;
            if ((float)valueInt == pGhost->value && valueInt > 0) {
                // Compute floor(log2(valueInt-1)) using bit-scan table
                uint32_t v = valueInt - 1;
                uint32_t level;
                if (v < 0x10000) {
                    if (v < 0x100) {
                        if (v == 0) {
                            level = 0xFFFFFFFF; // should not happen
                        } else {
                            level = bitScanTable[v & 0xFF];
                        }
                    } else {
                        level = bitScanTable[(v >> 8) & 0xFF] + 8;
                    }
                } else if (v < 0x1000000) {
                    level = bitScanTable[(v >> 16) & 0xFF] + 16;
                } else {
                    level = bitScanTable[v >> 24] + 24;
                }
                // Update histogram at index level+1 (level+1 is the bucket, e.g., 1..32)
                histogram[level + 1]++;
                (*pOutCount)++;
            }
        }
        totalNonZero++;
    }

    // Call finalizer
    finalizeDistribution(totalNonZero, pOutCount, param3);
}