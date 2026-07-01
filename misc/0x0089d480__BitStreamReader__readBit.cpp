// FUNC_NAME: BitStreamReader::readBit
void __thiscall BitStreamReader::readBit(void* this)
{
    // +0x18: current bit position in stream
    uint32_t currentBitPos = *(uint32_t*)((uint8_t*)this + 0x18);
    // +0x2c: maximum bit position (end of valid data)
    uint32_t maxBitPos = *(uint32_t*)((uint8_t*)this + 0x2c);

    // If we've reached or exceeded the limit, set error flag and stop
    if (maxBitPos < currentBitPos) {
        // +0x1c: error flag (set to 1 on overflow)
        *(uint8_t*)((uint8_t*)this + 0x1c) = 1;
        return;
    }

    // +0x0c: pointer to the byte array containing the bit stream
    uint8_t* bitArray = *(uint8_t**)((uint8_t*)this + 0x0c);
    uint8_t byteAtPos = bitArray[currentBitPos >> 3]; // byte containing the bit
    uint8_t bitMask = (uint8_t)(1 << (currentBitPos & 7));

    // Advance the bit position
    *(uint32_t*)((uint8_t*)this + 0x18) = currentBitPos + 1;

    // Check if the current bit is set
    if ((byteAtPos & bitMask) != 0) {
        // Bit is set – perform additional processing (possibly error recovery or extended data read)
        // These calls look like debug/logging with a size/type parameter 0x20
        FUN_0064b9e0(0x20, &this); // repeated four times – possibly stack trace or assert
        FUN_0064b9e0(0x20, &this);
        FUN_0064b9e0(0x20, &this);
        FUN_0064b9e0(0x20, &this);
        FUN_004a8ec0(0); // clear some error/flag
        // local_8 is an 8-byte buffer; read additional data into it
        uint8_t buffer[8];
        FUN_004a9360(this, buffer);
    }
    // If bit is not set, no further action – caller checks state or reads more bits later
}