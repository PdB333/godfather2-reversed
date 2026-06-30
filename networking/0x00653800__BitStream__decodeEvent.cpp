// FUNC_NAME: BitStream::decodeEvent
void __thiscall BitStream::decodeEvent(void *this, EventData *output)
{
    uint localBitIndex = *(uint *)((int)this + 0x18);
    uint totalBits = *(uint *)((int)this + 0x2c);
    uint8 *buffer = *(uint8 **)((int)this + 0xc);

    // Check if we've exhausted the bit stream
    if (totalBits < localBitIndex)
    {
        *(uint8 *)((int)this + 0x1c) = 1; // Set error flag
        return;
    }

    // Read first bit: check bit at position localBitIndex in the buffer
    uint byteOffset = localBitIndex >> 3;
    uint bitInByte = localBitIndex & 7;
    uint8 firstBit = (buffer[byteOffset] >> bitInByte) & 1;
    uint nextBitIndex = localBitIndex + 1;
    *(uint *)((int)this + 0x18) = nextBitIndex;

    if (firstBit != 0)
    {
        // First bit is 1 -> need to read another bit for the two-bit prefix
        if (totalBits < nextBitIndex)
        {
            *(uint8 *)((int)this + 0x1c) = 1;
            return;
        }

        uint8 secondBit = (buffer[nextBitIndex >> 3] >> (nextBitIndex & 7)) & 1;
        uint thirdBitIndex = localBitIndex + 2;
        *(uint *)((int)this + 0x18) = thirdBitIndex;

        if (secondBit != 0)
        {
            // Prefix "11" -> set a flag on the output and stop
            output->flags |= 8; // Bit 3 set
            return;
        }
        else
        {
            // Prefix "10" -> decode four 32-bit values from the rest of the stream
            uint value0 = call_ReadBits(this); // 0x00652840
            output->member_f0 = value0;
            uint value1 = call_ReadBits(this);
            output->member_ec = value1;
            uint value2 = call_ReadBits(this);
            output->member_e8 = value2;
            uint value3 = call_ReadBits(this);
            output->member_e4 = value3;
            call_ProcessDecodedEvent(); // 0x006538d0
        }
    }
    // If first bit is 0, the function returns without any action (default case)
    return;
}