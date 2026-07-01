// FUNC_NAME: TNLConnection::processReliableSlots
void __thiscall TNLConnection::processReliableSlots(uint mask) {
    int entryOffset;
    uint slotIdx;
    byte timeStamp[12]; // time buffer used for packet sequencing

    // Call internal time retrieval (likely returns current time or sequence number)
    (this->getTimeFunc)(this->statePtr, timeStamp);

    slotIdx = 0;
    if (this->reliableCount != 0) {
        entryOffset = 0;
        do {
            // Check if this slot is requested by the mask and is a waiting reliable packet (bit1 set at offset +0x8)
            if ((mask & (1 << (slotIdx & 0x1f))) != 0 &&
                ((*(uint *)(this->reliableEntries + entryOffset + 8) >> 1 & 1) != 0)) {
                // Process the reliable packet for this slot
                FUN_00897520(slotIdx, this->reliableEntries + entryOffset, timeStamp);
            }
            slotIdx++;
            entryOffset += 0x10; // each entry is 0x10 bytes
        } while (slotIdx < (uint)this->reliableCount);
    }
    return;
}