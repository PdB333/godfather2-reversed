// FUNC_NAME: StreamReader::readPacketLength
int __thiscall StreamReader::readPacketLength(void)
{
    // Structure fields:
    // +0x00: buffer (char*)
    // +0x10: readOffset (int)
    // +0x14: currentPtr (char*)
    // +0x18: lastReadValue (int)

    int offset = this->readOffset;          // +0x10
    char* base = this->buffer;              // +0x00

    // Read 4 bytes little-endian from buffer at current offset
    byte b0 = base[offset];
    byte b1 = base[offset + 1];
    byte b2 = base[offset + 2];
    byte b3 = base[offset + 3];
    int rawValue = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;

    // Advance offset by 4 bytes
    int newOffset = offset + 4;
    this->readOffset = newOffset;           // +0x10
    this->currentPtr = base + newOffset;    // +0x14

    // Store the value minus 8 (likely to strip an 8-byte header length)
    int storedValue = rawValue - 8;
    this->lastReadValue = storedValue;      // +0x18

    // Return a packed value: low byte forced to 1 (success flag),
    // upper 24 bits are the high 24 bits of storedValue.
    return (storedValue & 0xFFFFFF00) | 1;
}