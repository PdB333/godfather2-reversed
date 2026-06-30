// FUNC_NAME: BitStream::readBit
uint __fastcall BitStream::readBit(int this_ptr)
{
    // Structure fields:
    // +0x0c: pointer to buffer (byte*)
    // +0x18: current read bit position (uint)
    // +0x1c: overflow flag (byte)
    // +0x2c: total number of bits in stream (uint)

    uint readPos = *(uint*)(this_ptr + 0x18);

    // Check for overflow (read beyond end of stream)
    if (readPos >= *(uint*)(this_ptr + 0x2c))
    {
        *(byte*)(this_ptr + 0x1c) = 1; // Set overflow flag
        // Original returned (in_EAX & 0xFFFFFF00); assume EAX context unknown -> return 0
        return 0;
    }

    byte* buffer = *(byte**)(this_ptr + 0x0c);
    byte byteVal = buffer[readPos >> 3];
    byte bitIndex = (byte)(readPos & 7);
    bool bitSet = (byteVal & (1 << bitIndex)) != 0;

    // Advance read position
    *(uint*)(this_ptr + 0x18) = readPos + 1;

    // Build return value: high 24 bits = (readPos >> 11), low byte = 0 or 1 (the extracted bit)
    return ((readPos >> 11) << 8) | (uint)(bitSet ? 1 : 0);
}