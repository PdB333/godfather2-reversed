// FUNC_NAME: TNLBitStream::readSignedBits
// Reads a signed integer from the bitstream. The first bit is the sign flag, followed by (numBits-1) magnitude bits.
// Returns the signed value. If overflow (bit position exceeds total bits), sets overflow flag and returns 0 (unsigned).
uint32_t TNLBitStream::readSignedBits(uint32_t numBits)
{
    uint32_t currentBitPos = this->bitPosition; // +0x18
    if (this->totalBits < currentBitPos)        // +0x2c
    {
        this->overflowFlag = 1;                 // +0x1c
    }
    else
    {
        // Read the sign bit from the bit-packed buffer at this->buffer + (currentBitPos>>3)
        uint8_t byteVal = *(uint8_t*)(this->buffer + (currentBitPos >> 3)); // +0x0c
        this->bitPosition = currentBitPos + 1;  // increment bit position

        // Check sign flag
        if (byteVal & (1 << (currentBitPos & 7)))
        {
            // Signed: read magnitude bits (numBits-1) and negate
            uint32_t magnitudeBits = numBits - 1;
            uint32_t rawValue = 0;
            FUN_0064b9e0(magnitudeBits, &rawValue);  // helper reads 'magnitudeBits' bits into rawValue

            if (magnitudeBits == 32)
            {
                return -(int32_t)rawValue;
            }
            // Sign-extend negative value
            uint32_t mask = (1 << magnitudeBits) - 1;
            return -(int32_t)(rawValue & mask);
        }
    }

    // Unsigned case (no sign bit set, or overflow): read magnitude bits and return positive value
    uint32_t magnitudeBits = numBits - 1;
    uint32_t rawValue = 0;
    FUN_0064b9e0(magnitudeBits, &rawValue);

    if (magnitudeBits == 32)
    {
        return rawValue;
    }
    uint32_t mask = (1 << magnitudeBits) - 1;
    return rawValue & mask;
}