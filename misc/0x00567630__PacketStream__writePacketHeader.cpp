// FUNC_NAME: PacketStream::writePacketHeader
void __thiscall PacketStream::writePacketHeader(int this, int packetTypeOrSeq)
{
    char headerBuffer[76]; // +0x00 local buffer for packet header data (size 76 bytes)
    if (*(int*)(this + 0x0C) != 0) { // check if internal stream pointer is valid
        BitStream::writeU32(packetTypeOrSeq, 0, 0, 0); // write 32-bit value (packet type/seq) with zeros
        (**(code**)(**(int**)(this + 0x0C) + 0x54))(headerBuffer); // call virtual writeBytes on stream (vtable+0x54)
        BitStream::endWrite(); // finalize write operation
    }
}