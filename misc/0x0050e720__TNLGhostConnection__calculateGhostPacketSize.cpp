// FUNC_NAME: TNLGhostConnection::calculateGhostPacketSize
// Address: 0x0050e720
// Calculates buffer size for a ghost update packet based on item count, flags, and state.

int TNLGhostConnection::calculateGhostPacketSize(uint *thisPtr, uint *outType)
{
    // Get pointer to internal packet data (offset +0x04 from this)
    uint *dataPtr = (uint *)thisPtr[1]; // +0x04: pointer to ghost data structure

    // Number of ghost items (short at +0x11a)
    short numItems = *(short *)((char *)dataPtr + 0x11a);

    // Flags for the packet (uint at +0x104)
    uint dataFlags = *(uint *)((char *)dataPtr + 0x104);

    // Ghost state (byte at +0x154)
    char state = *(char *)((char *)dataPtr + 0x154);

    // Ceiling division by 8 for block count: (numItems+7)/8
    int numBlocks = (numItems + 7) >> 3;

    // Base size: aligned to 8 bytes + header (0xb0 = 176 bytes)
    int packetSize = numBlocks * 8 + 0xb0;

    // If flag 0x2000 is set, add additional per-block overhead (0x60 = 96 bytes)
    if ((dataFlags & 0x2000) != 0) {
        packetSize += numBlocks * 0x60;
    }

    // For certain states (1,2,6), add extra per-block overhead (0x20 = 32 bytes)
    if ((state == 1) || (state == 2) || (state == 6)) {
        packetSize += numBlocks * 0x20;
    }

    // Mark the output type as 0x10 (packet type identifier)
    *outType = 0x10;

    // Clear bit 1 of this->flags (likely a "dirty" or "needs rebuild" flag)
    *thisPtr &= 0xfffffffd;

    return packetSize;
}