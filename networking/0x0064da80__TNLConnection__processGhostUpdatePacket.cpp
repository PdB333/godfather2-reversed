//FUNC_NAME: TNLConnection::processGhostUpdatePacket
void __thiscall TNLConnection::processGhostUpdatePacket(int this, int packetBuffer, BitStream* stream)
{
    // Validate packet type based on connection state and buffer pointers
    // +0x210: pointer to reliable packet buffer? +0x1fc: pointer to another buffer?
    // +0x24: connection state (1=ghosting, 2=normal, 3=disconnected?)
    if ((((*(int*)(packetBuffer + 0x210) == 0) || (*(int*)(this + 0x24) != 1)) &&
         ((*(int*)(packetBuffer + 0x1fc) == 0 || (*(int*)(this + 0x24) != 2)))) &&
        (*(int*)(this + 0x24) != 3)) {
        FUN_00653080("Invalid Packet.");
        return;
    }

    uint bitPos = stream->bitPosition; // +0x18
    if (stream->totalBits < bitPos) { // +0x2c
        stream->errorFlag = 1; // +0x1c
        return;
    }

    // Read a bit from the stream (ghost update present flag)
    byte bit = *(byte*)((bitPos >> 3) + stream->buffer); // +0xc
    stream->bitPosition = bitPos + 1;
    if ((bit & (1 << (bitPos & 7))) != 0) {
        // Read 10-bit ghost index
        uint ghostIndex;
        readBits(10, &ghostIndex); // FUN_0064b9e0
        ghostIndex &= 0x3ff;

        // Call virtual function on ghost manager (this+0x14) to process the update
        // vtable offset 4 = second virtual function
        (**(code**)(**(int**)(this + 0x14) + 4))(stream);

        // Read another bit (ack flag?)
        bitPos = stream->bitPosition;
        if (stream->totalBits < bitPos) {
            stream->errorFlag = 1;
        } else {
            bit = *(byte*)((bitPos >> 3) + stream->buffer);
            stream->bitPosition = bitPos + 1;
            if ((bit & (1 << (bitPos & 7))) != 0) {
                // Acknowledge packet at index ghostIndex * 0x30
                FUN_00452df0(*(undefined4*)(*(int*)(packetBuffer + 0x214) + ghostIndex * 0x30));
                return;
            }
        }

        // If ghostIndex is invalid (0x3FF?), free the packet
        if (ghostIndex == 0xffffffff) { // Note: likely a decompilation artifact, should be 0x3FF?
            FUN_00452df0(0);
            return;
        }
        // Otherwise, free the packet at ghostIndex * 4 from another buffer
        FUN_00452df0(*(undefined4*)(*(int*)(packetBuffer + 0x210) + ghostIndex * 4));
    }
}