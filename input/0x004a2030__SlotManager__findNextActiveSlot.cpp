// FUNC_NAME: SlotManager::findNextActiveSlot
void SlotManager::findNextActiveSlot(uint* cursor, uint* outSlot) {
    // Base of 12-slot array at +0x88, each slot 12 bytes (0xc), first 4 bytes are pointer/ID.
    // Current index stored at +0x118.
    if (cursor == nullptr) {
        // Use the stored current index if no cursor provided.
        *outSlot = *(uint*)((uint)this + 0x88 + *(int*)((uint)this + 0x118) * 12);
        return;
    }
    uint nextVal = *cursor;
    for (int i = 0; i < 11; i++) {
        nextVal++;
        uint slotAddr = (uint)this + 0x88 + (nextVal % 12) * 12;
        if (*(int*)slotAddr != 0) {
            *outSlot = *(uint*)slotAddr;
            return;
        }
    }
    // No next active slot found; outSlot unchanged.
}