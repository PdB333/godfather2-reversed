// FUNC_NAME: EventScheduler::processScheduledEvent
// Address: 0x00624c20
// Processes a scheduled event from an event data packet.
// Handles two event types:
//   Type 1: Update internal flags based on packet header and dispatch items to a virtual handler.
//   Type 2: If a certain flag is not set and a counter is non-zero, call an internal update function.

int __thiscall EventScheduler::processScheduledEvent(int *this, void *context1, void *context2, void *context3, int eventType, EventSource *eventData)
{
    byte *packetHeader;
    ushort itemCount;

    if (eventType == 1) {
        // Type 1: Process packet list
        packetHeader = *(byte **)(eventData + 4); // +0x04: pointer to packet header
        if ((*packetHeader & 1) == 0) {
            this[5] = this[5] & 0xfffffffb; // Clear bit 2 (0x4) in flags at this+0x14
        } else {
            this[5] = this[5] | 4;           // Set bit 2 in flags
        }
        itemCount = 0;
        if (*(short *)(packetHeader + 2) != 0) { // +0x02: number of items
            do {
                // Call virtual function at vtable+0x20 (index 8) with context and each item pointer
                (**(code **)(*this + 0x20))(context1, context2, *(undefined4 *)(*(int *)(packetHeader + 4) + (uint)itemCount * 4));
                itemCount = itemCount + 1;
            } while (itemCount < *(ushort *)(packetHeader + 2));
        }
    }
    else {
        if (eventType != 2) {
            return 0; // Unknown event type
        }
        // Type 2: Update check
        if (((*(byte *)(this + 5) & 2) == 0) && (this[6] != 0)) {
            // Bit 1 (0x2) is clear and counter (this+0x18) is non-zero → call internal update
            FUN_00624f30(this);
            return 1;
        }
    }
    return 1;
}