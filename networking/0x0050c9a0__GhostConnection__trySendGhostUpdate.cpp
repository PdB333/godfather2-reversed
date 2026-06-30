// FUNC_NAME: GhostConnection::trySendGhostUpdate
void GhostConnection::trySendGhostUpdate(int objectIndex, int *packetInfo) {
    // Check if ghosting is allowed for this object index (bitmask at per-thread data)
    // Per-thread data structure offset: FS:[0x2c] -> pointer -> deref+8 gives base
    // Then index into array of 0x50 sized entries, plus 0x54 offset, plus *packetInfo byte
    uint *perThreadBase = *(uint **)(*(uint *)(__readfsdword(0x2c)) + 8);
    if ((*(byte *)((int)perThreadBase + objectIndex * 0x50 + 0x54 + *packetInfo) & 4) != 0) {
        return; // Ghosting disabled for this object/packet
    }

    // Get pointer to object data at this+0x24
    ObjectData *objData = *(ObjectData **)(this + 0x24);
    // Check if object has any non-zero position/rotation components
    // Offsets: +0x40 (x), +0x44 (y), +0x48 (z), +0x4C (w?)
    bool hasData = (objData->x != 0 || objData->y != 0 || objData->z != 0 || objData->w != 0);
    if (!hasData) return;
    // Redundant check (likely debug code)
    if (!(objData->x != 0 || objData->y != 0 || objData->z != 0 || objData->w != 0)) return;

    // Get packet manager singleton
    PacketManager *pktMgr = GetPacketManager(); // FUN_004e0f60
    if (pktMgr == nullptr) return;
    int streamHandle = pktMgr->streamHandle; // First field
    if (streamHandle == 0) return;

    // Local buffer for ghost update data (size 76 bytes)
    char buffer[76];
    int *bufferEnd = (int *)(buffer + 72); // +72? Actually local_54 is after 76 bytes, but we treat as part of buffer structure

    // Choose update function based on connection state
    if (*(byte *)(this + 0x5B) == 0x06) { // GhostUpdate type
        BuildGhostUpdateCompact(this, packetInfo, objectIndex, buffer); // FUN_00510740
    } else {
        BuildGhostUpdateFull(this, packetInfo, objectIndex); // FUN_00510f60
    }

    // Send the packet via stream
    SendStream(streamHandle, buffer, *(int *)(*(int *)(this + 4) + 0x84), 0); // FUN_004df210

    // Clear last pointer in buffer (if any)
    if (*bufferEnd != 0) {
        *(int *)(*bufferEnd + 8) = 0;
    }
}