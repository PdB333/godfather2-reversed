// FUNC_NAME: NetGhost::processGhostMessage
void __thiscall NetGhost::processGhostMessage(int thisPtr, void* packetStream) {
    // Virtual call to get message type (likely a hash)
    uint32_t messageHash = (*(uint32_t(**)(void*))packetStream)(packetStream);

    if (messageHash < 0x1b2d5c52) {
        if (messageHash == 0x1b2d5c51) {
            // Message: initial setup or header
            readPacketHeader();                    // FUN_00755a10
            // Write sequence or timestamp into packet at offset 0x60
            *(uint32_t*)((uint8_t*)packetStream + 0x60) = g_someGlobal; // DAT_00d64b8c
            return;
        }
        if (messageHash == 0x5be975d) {
            // Message: transform/state update (send direction)
            int state = *(int*)(thisPtr + 0x98);
            if (state != 0 && state != 0x48) {    // check state validity
                preparePacket();                   // FUN_00752080
                // Write part of state to packet (offsets 0x1b,0x1d word-aligned)
                *(uint64_t*)((uint8_t*)packetStream + 0x6c) = *(uint64_t*)(thisPtr + 0xb0);
                *(uint32_t*)((uint8_t*)packetStream + 0x74) = *(int*)(thisPtr + 0xb8);
                // Pack position/velocity (3 x 8-byte chunks)
                packTransformData(
                    *(uint64_t*)(thisPtr + 0xd0),
                    *(uint64_t*)(thisPtr + 0xd8),
                    *(uint64_t*)(thisPtr + 0xe0)
                ); // FUN_00751d50
                // Pack rotation/angular (3 x 8-byte chunks)
                packOtherData(
                    *(uint64_t*)(thisPtr + 0xe8),
                    *(uint64_t*)(thisPtr + 0xf0),
                    *(uint64_t*)(thisPtr + 0xf8)
                ); // FUN_00751d80
            }
            return;
        }
        else if (messageHash == 0x17a70916) {
            // Message: full update with reading (receive direction)
            readPacketHeader();                    // FUN_0075cd50
            // Read position/velocity into object fields (functions use current values as outputs?)
            readTransformData(
                *(uint64_t*)(thisPtr + 0xd0),
                *(uint64_t*)(thisPtr + 0xd8),
                *(uint64_t*)(thisPtr + 0xe0)
            ); // FUN_0073ad80
            // Read rotation/angular
            readOtherData(
                *(uint64_t*)(thisPtr + 0xe8),
                *(uint64_t*)(thisPtr + 0xf0),
                *(uint64_t*)(thisPtr + 0xf8)
            ); // FUN_0073adb0
            // Apply additional state change (takes thisPtr + offset and constants)
            readAdditionalState(
                (void*)(thisPtr + 0x00),           // 0x00751fe0 is likely a global constant
                0,
                0x75204000000000
            ); // FUN_0073ade0
            return;
        }
    }
    else if (messageHash == 0xa276bbeb) {
        // Message: full state snapshot (send direction)
        // Write entire state block from object to packet
        *(uint64_t*)((uint8_t*)packetStream + 0x90) = *(uint64_t*)(thisPtr + 0xa4); // offset 0x24*4
        *(uint32_t*)((uint8_t*)packetStream + 0x98) = *(int*)(thisPtr + 0xac);      // offset 0x26*4
        *(uint64_t*)((uint8_t*)packetStream + 0x9c) = *(uint64_t*)(thisPtr + 0xb0); // offset 0x27*4
        *(uint32_t*)((uint8_t*)packetStream + 0xa4) = *(int*)(thisPtr + 0xb8);      // offset 0x29*4

        // Write position/velocity chunk
        uint64_t v1 = *(uint64_t*)(thisPtr + 0xd8);
        uint64_t v2 = *(uint64_t*)(thisPtr + 0xe0);
        *(uint64_t*)((uint8_t*)packetStream + 0xb4) = *(uint64_t*)(thisPtr + 0xd0); // offset 0x2d*4
        *(uint64_t*)((uint8_t*)packetStream + 0xbc) = v1;                          // offset 0x2f*4
        *(uint64_t*)((uint8_t*)packetStream + 0xc4) = v2;                          // offset 0x31*4

        // Write rotation/angular chunk
        v1 = *(uint64_t*)(thisPtr + 0xf0);
        v2 = *(uint64_t*)(thisPtr + 0xf8);
        *(uint64_t*)((uint8_t*)packetStream + 0xcc) = *(uint64_t*)(thisPtr + 0xe8); // offset 0x33*4
        *(uint64_t*)((uint8_t*)packetStream + 0xd4) = v1;                          // offset 0x35*4
        *(uint64_t*)((uint8_t*)packetStream + 0xdc) = v2;                          // offset 0x37*4
    }
    return;
}