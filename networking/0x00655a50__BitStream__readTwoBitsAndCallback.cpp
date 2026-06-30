// FUNC_NAME: BitStream::readTwoBitsAndCallback
// Address: 0x00655a50
// Reads two consecutive bits from a bitstream and invokes a handler with the boolean values.
// The bitstream state is held in the object (this), and an external context (param_1) supplies a read-enable flag at offset 0x7c.

void BitStream::readTwoBitsAndCallback(void* context, uint param_2)
{
    byte localBuffer[12]; // Temporary buffer used by bitstream initialization (size unknown)

    // Only proceed if reading is enabled for this context
    if (*(byte*)((uint)context + 0x7c) != 0)
    {
        // Likely initializes or refills the bitstream's internal byte buffer (size 0x40? unclear)
        FUN_0064b9e0(0x40, localBuffer);

        // --- Read first bit ---
        uint bitIdx = this->m_bitIndex;          // +0x18: current bit position
        uint maxBits = this->m_maxBits;          // +0x2c: total bits in stream
        bool bit1;
        if (maxBits < bitIdx)
        {
            this->m_overflowFlag = 1;            // +0x1c: set overflow marker
            bit1 = false;
        }
        else
        {
            byte* bitBuffer = this->m_bitBuffer; // +0xc: pointer to bit array
            bit1 = ((bitBuffer[bitIdx >> 3] >> (bitIdx & 7)) & 1) != 0;
            this->m_bitIndex = bitIdx + 1;
        }

        // --- Read second bit ---
        bitIdx = this->m_bitIndex;
        bool bit2;
        if (maxBits < bitIdx)
        {
            this->m_overflowFlag = 1;
            bit2 = false;
        }
        else
        {
            byte* bitBuffer = this->m_bitBuffer;
            bit2 = ((bitBuffer[bitIdx >> 3] >> (bitIdx & 7)) & 1) != 0;
            this->m_bitIndex = bitIdx + 1;
        }

        // Pass the two bits to the processing callback
        FUN_00655b10(param_2, bit1, bit2);
    }
}