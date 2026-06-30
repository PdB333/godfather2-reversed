// FUNC_NAME: PacketBuffer::initialize
void PacketBuffer::initialize(uint param1, uint param2, uint param3, void* parent) {
    // +0x00: flags (bitfield)
    flags = (flags & 0xFFFF800A) | 0x000A; // keep high bits, set bits 1 and 3 (0xA)
    // +0x02: reserved (uint16)
    *(uint16*)((uint8*)this + 2) = 0;
    flags |= 0x8000; // set bit 15 (sequence-related flag?)
    // +0x04: uint16 (set to 4)
    *(uint16*)((uint8*)this + 4) = 4;
    // +0x06: uint16 (set to 0)
    *(uint16*)((uint8*)this + 6) = 0;
    // +0x08: pointer to internal buffer at +0x0C
    this->bufferPtr = (uint8*)(this + 3);
    // +0x0C: 64-byte buffer cleared
    memset(this + 3, 0, 0x40);
    // +0x4C: store param2 (likely window start or ack number)
    this->field_0x4C = param2;
    // +0x50: store param1 (likely sequence number)
    this->field_0x50 = param1;
    // +0x58: store parent pointer (from EDI)
    this->field_0x58 = (uint)parent;
    // +0x54: store param3 (unknown)
    this->field_0x54 = param3;

    // If parent is not a sentinel (DAT_0119cbbc), check its state
    if (parent != reinterpret_cast<void*>(DAT_0119cbbc)) {
        uint state = *(uint*)parent & 0x7FFF;
        // Re-initialize only if state is not 0x19 (25) and either bit 15 is clear
        // or state is not one of {0x0B, 0x18, 0x17} (11, 24, 23)
        if (state != 0x19 &&
            (!(parentFlags & 0x8000) || (state != 0x0B && state != 0x18 && state != 0x17))) {
            // This likely cleans up the parent's previous state
            FUN_0059c230(parent);
        }
    }
}