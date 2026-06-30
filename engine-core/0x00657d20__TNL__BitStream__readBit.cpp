// FUNC_NAME: TNL::BitStream::readBit
// Address: 0x00657d20
// Reads a single bit from the bitstream and returns success status.
// Object layout (__thiscall):
//   +0x00: vtable pointer
//   +0x04-0x0B: unknown
//   +0x0C: buffer (byte*) – pointer to raw byte array
//   +0x18: bitPosition (uint) – current bit index
//   +0x1C: errorFlag (byte) – set to 1 on overread
//   +0x2C: totalBits (uint) – total number of bits in stream

bool __thiscall BitStream::readBit(bool& outBit) {
    uint curPos = *(uint*)(this + 0x18);
    uint total = *(uint*)(this + 0x2C);

    if (total < curPos) {
        // Overread: set error flag and output 0
        *(byte*)(this + 0x1C) = 1;
        outBit = false;
        // Return true if error flag is zero (i.e., no error)? Actually returns error flag == 0.
        return *(char*)(this + 0x1C) == '\0';
    }

    byte* buf = *(byte**)(this + 0x0C);
    // Extract the bit: byte index = curPos >> 3, bit mask = 1 << (curPos & 7)
    byte bitByte = buf[curPos >> 3];
    byte bitMask = (byte)(1 << (curPos & 7));
    outBit = (bitByte & bitMask) != 0;

    // Advance bit position
    *(uint*)(this + 0x18) = curPos + 1;

    // Return success (error flag remains unchanged unless previously set)
    return *(char*)(this + 0x1C) == '\0';
}