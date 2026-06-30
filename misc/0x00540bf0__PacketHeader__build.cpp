// FUNC_NAME: PacketHeader::build
void __thiscall PacketHeader::build(uint* this, uint param2, uint param3, uint param4, uint param5, uint param6, uint param7)
{
    // Bits 0-4: param2 (5-bit value, e.g., sub-type)
    // Bits 5-9: constant 0x3e0 (fixed flags)
    // Bits 16-27: param3 low 12 bits (e.g., object ID or sequence)
    this[0] = (param3 & 0xfff) << 0x10 | (param2 & 0x1f) | 0x3e0;
    this[1] = param4; // +0x04
    this[2] = param5; // +0x08
    this[3] = param6; // +0x0c
    this[4] = param7; // +0x10
}