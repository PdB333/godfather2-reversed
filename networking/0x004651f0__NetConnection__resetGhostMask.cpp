// FUNC_NAME: NetConnection::resetGhostMask
// Reconstructed from address 0x004651f0
// This function resets the ghost bitmask for a specific connection slot.
// Each slot is 0x168 bytes, param_2 is the slot index (0-31).
// It clears the bitmask buffer, then sets bits for all active ghosts.
// Also zeroes two 64-bit fields at offsets 0x18bc and 0x18c4 (likely sequence numbers).

struct GhostMaskDescriptor {
    uint8_t* buffer;   // +0x00
    uint32_t  pad;     // +0x04 (unused)
    uint16_t  count;   // +0x08 (stored in low 16 bits of a 32-bit field)
};

// Structure at slot+0x10 references a list node with a count at +0x02
struct GhostListNode {
    uint16_t count;    // +0x02
};

// Helper: checks if ghost index is active
extern bool isGhostIndexActive(uint32_t index); // FUN_004652a0

uint32_t NetConnection::resetGhostMask(uint8_t slotIndex) {
    // Compute base pointer for this slot
    uint8_t* slotBase = reinterpret_cast<uint8_t*>(this) + slotIndex * 0x168;

    // Retrieve mask descriptor pointer from slot+0x16c
    GhostMaskDescriptor* maskDesc = *reinterpret_cast<GhostMaskDescriptor**>(slotBase + 0x16c);
    uint32_t retVal = 0;

    if (maskDesc != nullptr) {
        // Clear the bitmask buffer if count is nonzero
        if (maskDesc->count != 0) {
            for (uint32_t i = 0; i < maskDesc->count; i++) {
                *(maskDesc->buffer + i) = 0;
            }
        }

        // Obtain the number of ghost entries from a dynamic list
        // slotBase+0x10 contains an index into an array of pointer references
        int32_t listIndex = *reinterpret_cast<int32_t*>(slotBase + 0x10);
        uint8_t* listBase = slotBase + 0x10; // base of pointer array
        GhostListNode* listNode = *reinterpret_cast<GhostListNode**>(listBase + listIndex * 4);
        uint32_t ghostCount = listNode->count;

        // Set bits for active ghosts
        if (ghostCount != 0) {
            for (uint32_t i = 0; i < ghostCount; i++) {
                if (isGhostIndexActive(i)) {
                    uint8_t* bytePtr = maskDesc->buffer + (i >> 3);
                    *bytePtr |= (1 << (i & 7));
                }
            }
        }

        retVal = reinterpret_cast<uint32_t>(maskDesc);
    }

    // Zero two 8‑byte fields at the connection level
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 0x18bc) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 0x18c4) = 0;

    return retVal;
}