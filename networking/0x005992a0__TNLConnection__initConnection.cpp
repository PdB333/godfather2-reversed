// FUNC_NAME: TNLConnection::initConnection
void __thiscall TNLConnection::initConnection(TNLConnection *this) {
    // Offset +0x00: flags field (bitmask). Clear bits 0,2-5? Set bit1 (value 2) and bits 6,7.
    this->flags = (this->flags & 0xffffffc2) | 2;

    // Clear fields at various offsets
    this->unk04 = 0;        // +0x04
    this->unk08 = 0;        // +0x08
    this->unk50 = 0;        // +0x50 (0x14*4)
    this->unk54 = 0;        // +0x54 (0x15*4)
    *(byte *)((uint)this + 0x58) = 0;  // +0x58 byte
    *(byte *)((uint)this + 0x79) = 0;  // +0x79 byte
    *(byte *)((uint)this + 0x9a) = 0;  // +0x9a byte
    *(byte *)((uint)this + 0x9b) = 0;  // +0x9b byte
    this->unk1BC = 0;       // +0x1BC (0x6f*4)
    this->unk1C0 = 0;       // +0x1C0 (0x70*4)
    this->unk1C4 = 0;       // +0x1C4 (0x71*4)
    this->unk1C8 = 0;       // +0x1C8 (0x72*4)

    // Clear the 32-slot transmit window (pairs of uint32 starting at +0xBC)
    // Each slot likely represents sequence number and status.
    uint* window = (uint*)((uint)this + 0xBC);
    for (int i = 0; i < 32; i++) {
        window[0] = 0;
        window[1] = 0;
        window += 2;
    }
}