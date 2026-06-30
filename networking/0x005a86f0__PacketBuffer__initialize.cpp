// FUNC_NAME: PacketBuffer::initialize
struct PacketBuffer {
    uint32_t flags;           // +0x00
    uint16_t field_2;         // +0x02
    uint16_t field_4;         // +0x04
    uint16_t field_6;         // +0x06
    uint32_t payloadPtr;      // +0x08 (points to +0x0C)
    uint8_t  payload[0x40];   // +0x0C (64 bytes)
    uint32_t sequenceParam;   // +0x4C
};

void __thiscall PacketBuffer::initialize(uint32_t param_1)
{
    this->flags = (this->flags & 0xffff8009) | 9;
    *(uint16_t*)((uint8_t*)this + 2) = 0;
    this->flags |= 0x8000;
    *(uint16_t*)((uint8_t*)this + 4) = 4;
    *(uint16_t*)((uint8_t*)this + 6) = 0;
    this->payloadPtr = (uint32_t)((uint8_t*)this + 0x0C);
    memset((uint8_t*)this + 0x0C, 0, 0x40);
    this->sequenceParam = param_1;
}