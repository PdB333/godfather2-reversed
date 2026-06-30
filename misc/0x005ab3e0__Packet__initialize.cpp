// FUNC_NAME: Packet::initialize
// Initializes a network packet structure with inline buffer (EARS engine)
void Packet::initialize() {
    uint32* flags = (uint32*)this;
    *flags = (*flags & 0xFFFF8016) | 0x16;   // +0x00: preserve flag bits, set default 0x16
    *(uint16*)((uint32)this + 2) = 0;        // +0x02: zero sub‑field (reserved/version)
    *flags |= 0x8000;                        // +0x00: set high flag (packet‑type bit)
    *(uint16*)((uint32)this + 4) = 4;        // +0x04: set field to 4 (max sequence? type?)
    *(uint16*)((uint32)this + 6) = 0;        // +0x06: zero another sub‑field
    *(uint32*)((uint32)this + 8) = (uint32)this + 12; // +0x08: pointer to inline buffer (offset +12)
    memset((void*)((uint32)this + 12), 0, 0x40); // +0x0C: zero 64‑byte inline buffer
    *(uint32*)((uint32)this + 0x4C) = 0;     // +0x4C: buffer length / capacity (reset)
    *(uint32*)((uint32)this + 0x50) = 0;     // +0x50: write position / bit count
    *(uint32*)((uint32)this + 0x54) = 0;     // +0x54: extra flags / state
}