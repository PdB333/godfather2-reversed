// FUNC_NAME: GhostManager::resolveGhostId
// Address: 0x00496710
// This function searches a global array of ghost IDs (matching against param_2) and either returns the index if found
// or appends the ID to the array if not found (up to capacity). It returns a packed 32-bit value for packet construction
// and also writes a 2-int result to the output pointer pointed by ESI (assumed to be a member or caller-provided buffer).
// The function appears to be part of the TNL ghost replication system (EARS engine).
//
// Global data:
// * ghostCount (0x01205460) - number of registered ghost IDs
// * ghostArray (0x01163f68) - array of ghost IDs (int[])

int __fastcall GhostManager::resolveGhostId(int this, int ghostId, short flags)
{
    int oldCount;
    int index;
    int result;
    bool capacityReached;

    oldCount = ghostCount;
    index = 0;
    if (ghostCount > 0) {
        do {
            if (ghostArray[index] == ghostId) {
                // Found existing ghost
                if (index != -1) {
                    goto found;
                }
                break;
            }
            index++;
        } while (index < ghostCount);
    }

    // Ghost not found; try to add it
    capacityReached = (ghostCount == -1); // -1 sentinel may indicate full/corrupted
    ghostArray[ghostCount] = ghostId;
    ghostCount++;
    index = oldCount; // Use the old count as the new index (position of added ghost)

    if (capacityReached) {
        return 0xFFFFFF00; // Error: maximum capacity reached or invalid state
    }

found:
    // Build a 32-bit packed value: [flags (16 bits)][(index+1) (8 bits)][0x02 (8 bits)]
    // and write it to the output buffer (ESI pointer assumed to be a GhostInfo structure)
    // +0x00: packedId
    // +0x04: zero (maybe timestamp or additional data)
    {
        int packedId = (flags << 16) | ((index + 1) << 8) | 0x02;
        *(int *)(this + 0x??) = packedId; // Assuming unaff_ESI is a member pointer, or we treat it as a global output
        // Actually in the original code, unaff_ESI is not derived from this. We will assume it is a member offset.
        // For reconstruction, we can treat it as *((int*)unaff_ESI) where unaff_ESI is passed via register.
        // Since we don't have the class layout, we'll document it as writing to a caller-provided buffer.
        // In the original, it does: *unaff_ESI = local_8; unaff_ESI[1] = 0;
        // Assume unaff_ESI = this->m_outputBuffer (offset TBD)
    }

    // Build return value: [index high 16 bits (if any)][flags high byte][0x01]
    result = ((index >> 16) << 16) | ((flags >> 8) << 8) | 0x01;
    return result;
}