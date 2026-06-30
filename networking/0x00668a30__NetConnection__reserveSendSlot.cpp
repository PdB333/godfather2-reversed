// FUNC_NAME: NetConnection::reserveSendSlot
// Address: 0x00668a30
// Role: Attempts to allocate a slot for sending reliable packets from a pool of 28-slot groups.
//       Uses a bitmask of used slots to quickly find the next slot, with linear fallback.

#include <cstdint>

class NetConnection {
public:
    int m_slotCount;          // +0x00: number of 28-slot groups
    int field_4;              // +0x04: unknown
    int field_8;              // +0x08: unknown
    uint32_t* m_slotBitmaskArray; // +0x0C: pointer to array of bitmasks (size m_slotCount)

    // Internal helper functions (offsets provided)
    int tryMarkSlot(int slotIndex);                      // 0x00665720
    int isSlotAvailable(int slotIndex);                  // 0x00668da0
    int getNextAvailableSlotIndex();                     // 0x00665c30 (returns -1 if none)
    int allocateAndFinalizeSlot(int slotIndex);          // 0x0066c8d0

    int reserveSendSlot(); // this function
};

int NetConnection::reserveSendSlot() {
    int groupCount = this->m_slotCount;
    if (groupCount == 0) {
        return 0; // no groups, cannot allocate
    }

    // Compute base slot index for the last group
    int baseSlot = (groupCount - 1) * 28;
    // Read bitmask of the last group
    uint32_t bitmask = this->m_slotBitmaskArray[groupCount - 1];
    // Count bits in binary representation (floor(log2)+1) - used to estimate next used slot?
    int highBitPos = 0;
    while (bitmask != 0) {
        bitmask >>= 1;
        highBitPos++;
    }
    // Candidate global slot index
    int candidateIndex = baseSlot + highBitPos;
    // Convert to a specific slot within the group for the marking attempt
    int slotToTry = (candidateIndex % 28) + (groupCount * 28) - 29;
    int result = this->tryMarkSlot(slotToTry);
    if (result == 0) {
        // Fallback: linear scan from (candidateIndex % 28) - 1 to 27
        int startSlot = (candidateIndex % 28) - 1;
        for (int i = startSlot; i < 28; ++i) {
            int avail = this->isSlotAvailable(i);
            if (avail != 0) {
                return avail;
            }
            int nextSlot = this->getNextAvailableSlotIndex();
            if (nextSlot != -1) {
                int allocResult = this->allocateAndFinalizeSlot(nextSlot);
                if (allocResult != 0) {
                    return allocResult;
                }
            }
        }
        result = 0;
    }
    return result;
}