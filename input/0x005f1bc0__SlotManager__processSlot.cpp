// FUNC_NAME: SlotManager::processSlot
void SlotManager::processSlot(EventObject* event) {
    // event + 0x3 holds the slot index (byte)
    uint8_t slotIndex = *(uint8_t*)((uintptr_t)event + 0x3);

    // m_slotArray at +0x30 points to an array of SlotData (size 0x94 each) with a 4-byte header
    // header: [uint16 count] [uint16 reserved]
    ushort* slotDataArray = *(ushort**)((uintptr_t)this + 0x30);

    if (slotDataArray != (ushort*)0xdeadbeef) {
        uint16 arrayCount = *slotDataArray; // first ushort: number of slots

        if (slotIndex < arrayCount) {
            // Each slot occupies 0x94 bytes; slots start after the header (4 bytes)
            // pointer arithmetic: base + index * sizeof(SlotData) + header_offset (in ushort units)
            ushort* slotData = slotDataArray + (uint32_t)slotIndex * 0x4a + 2;

            if (slotData != (ushort*)0x0) { // sanity check (always true if slotDataArray valid)
                // Notify the slot of the event
                FUN_005dbc10((int32_t)(int8_t)slotIndex);
                FUN_005f3590(slotData);
            }
        }
    }
}