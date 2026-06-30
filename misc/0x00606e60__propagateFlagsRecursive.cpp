// FUNC_NAME: propagateFlagsRecursive
void propagateFlagsRecursive(unsigned int nodeIndex, unsigned int flagsToSet)
{
    // Guard: invalid index (0xFFFFFFFF = -1) or out of range
    if (nodeIndex == 0xFFFFFFFF || nodeIndex >= 0x1000) {
        return;
    }

    // Each node is 0x38 bytes in the global array at g_nodeArray
    // Structure:
    // +0x00: byte state (0-3 allowed)
    // +0x0C: uint32 flags
    // +0x1C: int32 childIndex (or -1)
    static uint8_t* g_nodeArray = (uint8_t*)0x011a0f28; // global base

    uint8_t* node = g_nodeArray + nodeIndex * 0x38;

    // State must be < 4 (active?)
    if (node[0] >= 4) {
        return;
    }

    // Recursively propagate to child first
    int childIndex = *(int*)(node + 0x1C); // child at offset +0x1C
    if (childIndex != 0) {
        propagateFlagsRecursive((unsigned int)childIndex, flagsToSet);
    }

    // Conditionally update flags bits. Only set bits if the corresponding
    // field in flagsToSet is NOT equal to a specific "don't touch" pattern.
    // Masks: bits 12-14, 16-17, 20-22, 24-25
    uint32_t* flagsPtr = (uint32_t*)(node + 0x0C); // flags at offset +0x0C

    if ((flagsToSet & 0x7000) != 0x4000) {
        *flagsPtr = (*flagsPtr & ~0x7000) | (flagsToSet & 0x7000);
    }
    if ((flagsToSet & 0x30000) != 0x30000) {
        *flagsPtr = (*flagsPtr & ~0x30000) | (flagsToSet & 0x30000);
    }
    if ((flagsToSet & 0x700000) != 0x700000) {
        *flagsPtr = (*flagsPtr & ~0x700000) | (flagsToSet & 0x700000);
    }
    if ((flagsToSet & 0x3000000) != 0x3000000) {
        *flagsPtr = (*flagsPtr & ~0x3000000) | (flagsToSet & 0x3000000);
    }

    // Fire callback after update
    // (FUN_006189c0 likely signals a change or notifies listeners)
    notifyNodeChanged();
}