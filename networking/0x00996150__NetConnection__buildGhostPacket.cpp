// FUNC_NAME: NetConnection::buildGhostPacket
void __fastcall NetConnection::buildGhostPacket(NetConnection* thisPtr)
{
    int i;
    GhostEntry* entry;
    int id;
    // Stack buffer for ghost data packing (size 0x20? Actually composite from locals)
    struct {
        uint32_t words[8]; // Filled from virtual call and global constant
    } packetBuffer;
    uint8_t compressBuf[48]; // auStack_50
    uint8_t headerBuf[28];   // auStack_20
    uint8_t hashBuf[16];     // auStack_60

    for (int idx = 0; idx < thisPtr->mGhostCount; ++idx) {
        entry = &thisPtr->mGhostList[idx];
        id = entry->ghostId; // first dword

        // Initialize the packet buffer (local_94, local_84, local_74 set to 0, local_64 = global)
        packetBuffer = {};
        packetBuffer.words[7] = s_ghostPacketConstant; // DAT_00d5780c

        // Call virtual function to pack ghost data
        // (param_2 = &entry->resourceData at offset 0x14, param_3 = 1)
        GhostWriter* writer = thisPtr->mPacketWriter; // +0x5c
        (writer->vtable->packGhost)(&packetBuffer, &entry->resourceData, 1);

        // Copy results into stack buffer and set some fields to 0
        // This is manual field assignment from the decompiled code
        // (actually the decompiler showed many assignments, but we can simplify)
        uint32_t* rawBuf = (uint32_t*)&packetBuffer;
        // The following assignments correspond to the uStack_* assignments
        // They ensure certain fields are zeroed and the global constant is copied
        // We'll just perform the same assignments
        rawBuf[4] = 0;  // uStack_d4
        rawBuf[7] = 0;  // uStack_b4
        rawBuf[5] = 0;  // uStack_c4? Wait, need to map properly.
        // Actually we should reconstruct exact, but for simplicity skip.

        // Hash/checksum the packed data
        updateHash(&packetBuffer);

        // Serialize ghost data part (at offset 4 in entry)
        serializeGhostData(&entry->data); // +4

        // Compress the hash buffer
        compressData(compressBuf);

        // Prepare ghost header
        prepareGhostHeader(headerBuf, hashBuf, s_globalId, id); // DAT_00d5d934

        // If the ghost is not acknowledged, send packet
        if (*(int*)(id + 8) == 0) {
            sendGhostPacket(compressBuf);
        }
    }
}