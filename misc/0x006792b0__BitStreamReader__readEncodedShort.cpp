// FUNC_NAME: BitStreamReader::readEncodedShort
short __fastcall BitStreamReader::readEncodedShort(BitStreamReader* self)
{
    // BitStreamReader layout:
    // +0x00: currentByte (uint8_t*)
    // +0x04: nibbleOffset (int16_t) // 0 = byte aligned, 1 = half-byte aligned
    uint8_t*& buf = self->currentByte;
    int16_t& offset = self->nibbleOffset;

    int8_t firstPart;
    uint8_t secondPart;

    // Read first nibble pair (forms a byte)
    if (offset == 0) {
        firstPart = *buf;
        buf++;
    } else {
        // Combine low nibble of current byte with high nibble of next byte
        firstPart = (*buf * 16) + (*(buf + 1) >> 4);
        buf++;
    }

    // Read second nibble (4 bits)
    uint8_t curNibbleByte = *buf;
    self->currentByte = buf;
    if (offset == 0) {
        self->nibbleOffset = 1;
        secondPart = curNibbleByte >> 4; // high nibble
    } else {
        secondPart = curNibbleByte & 0xF; // low nibble
        self->nibbleOffset = 0;
        self->currentByte = buf + 1; // advance extra byte
    }

    short result = (firstPart * 16) + secondPart; // 12-bit base value

    // If base value < 0x80 (i.e., high 5 bits zero), read an extra byte
    if ((ushort)(result + 0x80U) < 0x100) {
        if (self->nibbleOffset == 0) {
            // Byte-aligned extension
            int8_t extra = *self->currentByte;
            self->currentByte++;
            result = result * 256 + (unsigned char)extra;
        } else {
            // Half-byte aligned extension
            int8_t extraByte = *self->currentByte;
            uint8_t* nextPtr = self->currentByte + 1;
            self->currentByte = nextPtr;
            int8_t extra = (*(nextPtr) >> 4) + (extraByte * 16);
            result = result * 256 + (unsigned char)extra;
        }
    }

    return result;
}