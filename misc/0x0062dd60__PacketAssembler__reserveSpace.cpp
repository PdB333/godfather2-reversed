// FUNC_NAME: PacketAssembler::reserveSpace
// Function at 0x0062dd60: Attempts to reserve 8 bytes in the packet buffer, rolling back if insufficient space.
// Internal helpers: FUN_0062dbc0 (resetBufferPosition), FUN_0062dc80 (hasSpaceFor, returns 0 if no space).

int PacketAssembler::reserveSpace() {
    // Reset current buffer write position to start of free area
    resetBufferPosition();

    // Check if there is enough space for an 8-byte write
    int spaceAvailable = hasSpaceFor(this);
    if (spaceAvailable == 0) {
        // Not enough space; roll back the write pointer by 8 bytes
        // Offset +0x08: m_writePos (current write pointer in buffer)
        *(int*)(this + 8) = *(int*)(this + 8) - 8;
    }
    return 1; // Always returns success (1)
}