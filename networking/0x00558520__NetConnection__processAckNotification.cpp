// FUNC_NAME: NetConnection::processAckNotification
// Address: 0x00558520
// Processes a packet ACK notification bitfield for 32-slot window.
// Parameters: param1 (stack arg), ackData (register ESI, pointer to ACK bitfield)
void NetConnection::processAckNotification(uint32_t param1) {
    // If notify list not initialized, set up using ackData
    if (this->notifyList == nullptr) {
        FUN_00558430(this->ackData); // initializeNotification
    }

    // Get notification value from notify list + 0x10
    uint32_t notifyValue = 0;
    if (this->notifyList != nullptr) {
        notifyValue = *(uint32_t*)(this->notifyList + 0x10);
    }

    uint32_t ackFlags = *this->ackData;          // original bitfield
    uint32_t highBits = ackFlags & 0xC0000000;  // top two bits indicate type

    if (highBits != 0) {
        if (highBits == 0x40000000) {
            // Single slot: use ackFlags as index into table at base 0 (global slot array)
            ackFlags = *(uint32_t*)(ackFlags * 4);
        } else if (highBits == 0xC0000000) {
            // Range slot: use ackFlags as index into table at base 0x4c
            ackFlags = *(uint32_t*)(ackFlags * 4 + 0x4c);
        } else {
            // Unknown high bits – fallback with slot = 0
            FUN_00557d80(notifyValue, param1, this->connectionId, 0);
            return;
        }
    }

    // Extract slot index (5 bits, 0-31)
    uint32_t slotIndex = ackFlags & 0x1F;
    FUN_00557d80(notifyValue, param1, this->connectionId, slotIndex);
}