// FUNC_NAME: TNLConnection::resetPacketWindow
void TNLConnection::resetPacketWindow() {
    // Set connection flags: clear bits 0,2,3,4,5; set bit 1 (likely "initialized" or "active")
    this->flags = (this->flags & 0xFFFFFFC2) | 2;

    // Zero out individual fields
    this->field_04 = 0;          // +0x04
    this->field_08 = 0;          // +0x08
    this->field_50 = 0;          // +0x50 (seq/ack related)
    this->field_54 = 0;          // +0x54
    *(uint8*)((uint32)this + 0x58) = 0; // +0x58
    *(uint8*)((uint32)this + 0x79) = 0; // +0x79
    *(uint8*)((uint32)this + 0x9A) = 0; // +0x9A
    *(uint8*)((uint32)this + 0x9B) = 0; // +0x9B

    // Reset packet window counters (4 uints at +0x1BC)
    this->field_1BC = 0;         // +0x1BC (last sequence or outstanding packets)
    this->field_1C0 = 0;         // +0x1C0
    this->field_1C4 = 0;         // +0x1C4
    this->field_1C8 = 0;         // +0x1C8

    // Clear all 32 packet slots (each slot is 8 bytes: 2 uint32)
    uint32* slotBase = reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0xBC);
    for (int i = 0; i < 32; ++i) {
        slotBase[0] = 0;
        slotBase[1] = 0;
        slotBase += 2; // Move to next slot (8 bytes)
    }
}