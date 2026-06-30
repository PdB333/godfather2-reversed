// FUNC_NAME: CommandManager::flushPendingEvents
void CommandManager::flushPendingEvents(EventEntry* events, int eventCount)
{
    // This structure is used to pack event data into 32-slot buffer for network transmission.
    // Each event entry is 24 bytes (6 uint32s).
    struct PackedEvent {
        uint32_t data[4]; // +0x00: 4 uint32s from source entry
    };

    // The packed buffer: count at index 128, then 32 PackedEvent entries.
    struct PackedBuffer {
        uint32_t count; // treated as array element 128
        PackedEvent events[32]; // indices 0..127
    };

    NetworkManager* netMgr = *(NetworkManager**)(*(uint32_t*)(DAT_01223448 + 0x10)); // global pointer to network manager
    if (netMgr != nullptr) {
        // Prepare for packing (likely lock or reset)
        FUN_0047ff10(); // unknown: prepareNetworkBuffer?

        PackedBuffer packed;
        packed.count = 0;

        uint32_t flags32 = 0; // used to build a 32-bit flag array
        uint32_t flagsIndex = 0;

        if (eventCount > 0) {
            EventOffset24* src = (EventOffset24*)((uint8_t*)events + 0x9C); // each entry is 24 bytes, starting at offset 0x9C from events base
            for (int i = 0; i < eventCount; i++) {
                // Pack into buffer if slots remain
                if (packed.count < 32) {
                    uint32_t idx = packed.count;
                    packed.events[idx].data[0] = src->field0;   // +0x00
                    packed.events[idx].data[1] = src->field4;   // +0x04
                    packed.events[idx].data[2] = src->field8;   // +0x08
                    packed.events[idx].data[3] = src->field12;  // +0x0C
                    packed.count++;
                }
                // Build flag bit field (only low bit of byte at +0x10 from source)
                if (flagsIndex < 32) {
                    flags32 |= ((src->field16 & 1) << flagsIndex); // pack bit into 32-bit uint
                    flagsIndex++;
                }
                src = (EventOffset24*)((uint8_t*)src + 24); // advance to next entry (6 uint32s)
            }
        }

        // Send packed data to network layer
        // Parameters: netMgr, packedBuffer, flags (stored in byte array representing bits), 
        // eventCount, and data at events + 0x20 (likely some header/context)
        FUN_004514c0(netMgr, &packed, (uint8_t*)&flags32, eventCount, (uint8_t*)events + 0x20);
    }
}