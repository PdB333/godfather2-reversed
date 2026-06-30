// FUNC_NAME: PacketWriter::writeCommand
void PacketWriter::writeCommand(void *this, uint param) {
    uint *bufferPtr = *(uint **)((int)this + 8); // +0x8: current write pointer in buffer
    *bufferPtr = 2;                               // command type (2)
    bufferPtr[1] = param;                         // command parameter
    *(int *)((int)this + 8) = (int)bufferPtr + 8; // advance pointer by 8 bytes
}