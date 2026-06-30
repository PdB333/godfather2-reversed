// FUN_00442bd0: SlotProcessor::refreshBindings
void SlotProcessor::refreshBindings()
{
    // +0x58: number of slots (uint16)
    uint slotCount = *(uint16*)(this + 0x58);
    // +0x0C: flags – set bit 2 (0x4) to mark update needed
    *(uint32*)(this + 0x0C) |= 4;

    if (slotCount != 0) {
        // +0x34: pointer to slot array, each slot 0x20 bytes
        uint8* slotArrayPtr = *(uint8**)(this + 0x34);
        for (uint i = 0; i < slotCount; ++i) {
            Slot* slot = reinterpret_cast<Slot*>(slotArrayPtr + i * 0x20);
            // +0x08: type identifier – skip known invalid type 0x32293930
            if (slot->typeId != 0x32293930) {
                // +0x0C: data pointer passed to getHandler
                int handler = FUN_00421170(&slot->data);
                if (handler != 0) {
                    // +0x1C: store resulting handler pointer
                    slot->handlerResult = handler;
                }
            }
        }
    }
}