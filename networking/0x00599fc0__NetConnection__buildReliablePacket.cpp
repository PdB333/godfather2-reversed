// FUNC_NAME: NetConnection::buildReliablePacket
void __fastcall NetConnection::buildReliablePacket(void* thisPtr) {
    PacketDescriptor* desc = *(PacketDescriptor**)((char*)thisPtr + 8);
    uint16_t expectedSize = (uint16_t)(desc->chunkCount * 0x10 + 0x18);
    if ((uint16_t)desc->bufferSize != expectedSize) {
        // Assert: buffer size mismatch
        ((void(*)(void))(*DAT_01205590 + 4))();
    }

    uint32_t sequenceNumber = ((uint32_t)desc->byte0 << 24) |
                              ((uint32_t)desc->byte1 << 16) |
                              ((uint32_t)desc->byte2 << 8)  |
                              (uint32_t)desc->byte3;

    PacketChunk* chunk = findOrCreateChunk(thisPtr, sequenceNumber); // FUN_00599aa0
    if (chunk == nullptr) {
        // Failed to allocate chunk – abort
        ((void(*)(void))(*DAT_01205590 + 4))();
        return;
    }

    int chunkCount = desc->chunkCount;
    if (chunkCount > 0xFFFF) {
        ((void(*)(void))(*DAT_01205590 + 4))();
    }

    int16_t countShort = (int16_t)chunkCount;
    if (countShort != 0) {
        chunk->field_0x18 = 0;                // +0x18: int (likely reserved)
        chunk->field_0x1c = 1;                // +0x1c: short (maybe flags)
        chunk->field_0x1e = countShort;       // +0x1e: short (chunk count)
        chunk->dataPointer = desc->data;      // +0x24: pointer to payload data (desc+0x18)
        chunk->field_0x20 = 1;                // +0x20: short (maybe another flag)
    }
    // Clear lower 2 bits (alignment or flag bits)
    chunk->field_0x10 &= ~3u;                 // +0x10: uint (flags/state)
}