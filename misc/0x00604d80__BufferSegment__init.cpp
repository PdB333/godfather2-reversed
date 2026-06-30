// FUNC_NAME: BufferSegment::init
void __thiscall BufferSegment::init(void* buffer)
{
    int count = *(int*)((uint8_t*)buffer + 0x10); // Number of 12-byte elements at offset +0x14
    this->start    = (uint8_t*)buffer;                     // +0x00: pointer to start of buffer
    this->start2   = (uint8_t*)buffer;                     // +0x04: duplicate start pointer
    this->array    = (uint8_t*)buffer + 0x14;              // +0x08: start of element array (after 0x14-byte header)
    this->arrayEnd = (uint8_t*)buffer + 0x14 + count * 12; // +0x0C: end of element array
}