// FUNC_NAME: TNLBitStream::readPackedChunk
void TNLBitStream::readPackedChunk()
{
    // +0x0c: pointer to byte buffer (bit data)
    // +0x18: current bit position (bit index)
    // +0x2c: total number of bits in buffer
    // +0x1c: overflow flag (byte)
    // +0x10? Not used here.

    FUN_00472c10(this); // likely bitstream::beginRead() or reset cursor

    uint currentBitIndex = *(uint *)(this + 0x18);
    uint totalBits = *(uint *)(this + 0x2c);

    // Read first flag bit
    if (totalBits < currentBitIndex) {
        *(byte *)(this + 0x1c) = 1; // overflow
    } else {
        byte currentByte = *(byte *)((currentBitIndex >> 3) + *(int *)(this + 0xc));
        *(uint *)(this + 0x18) = currentBitIndex + 1;
        if ((currentByte & (1 << (currentBitIndex & 7))) != 0) {
            // Magic signature for debug marker
            undefined4 headerSignature[4];
            headerSignature[0] = 0xbadbadba;
            headerSignature[1] = 0xbeefbeef;
            headerSignature[2] = 0xeac15a55;
            headerSignature[3] = 0x91100911;
            FUN_004a9cd0(this, headerSignature); // likely readPackedBlockWithMagic
        }
    }

    // Read second flag bit
    currentBitIndex = *(uint *)(this + 0x18);
    totalBits = *(uint *)(this + 0x2c);
    if (totalBits < currentBitIndex) {
        *(byte *)(this + 0x1c) = 1;
        return;
    }
    byte currentByte = *(byte *)((currentBitIndex >> 3) + *(int *)(this + 0xc));
    *(uint *)(this + 0x18) = currentBitIndex + 1;
    if ((currentByte & (1 << (currentBitIndex & 7))) != 0) {
        FUN_004a8ec0(0); // some other read operation
        FUN_004a9360(this, headerSignature); // reads data associated with the same signature
    }
}