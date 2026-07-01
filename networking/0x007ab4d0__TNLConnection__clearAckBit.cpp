// FUNC_NAME: TNLConnection::clearAckBit
void __thiscall TNLConnection::clearAckBit(int this, uint ackIndex)
{
    uint* ackBits;
    // +0x58: pointer to connection state data
    // +0x249c: offset to ack bitfield array (32-bit entries, one per packet window slot)
    ackBits = (uint*)(*(int*)(this + 0x58) + 0x249c + (ackIndex >> 5) * 4);
    *ackBits = *ackBits & ~(1 << (ackIndex & 0x1f));
    return;
}