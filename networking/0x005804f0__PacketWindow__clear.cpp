// FUNC_NAME: PacketWindow::clear
void PacketWindow::clear(void)
{
    // Global fill value (likely 0 or -1 for reset)
    uint32_t fillValue = DAT_00e2b1a4; // constant from .data

    // +0x0c: total number of elements to clear (interpreted as bit count? division by 8 suggests bytes or bits)
    int32_t elementCount = this->m_elementCount; // offset +0x0c

    // +0x10: start of the buffer array
    uint32_t *buffer = reinterpret_cast<uint32_t *>(this + 0x10);

    // Process full 32‑dword blocks (each block = 128 bytes)
    int32_t fullBlocks = elementCount >> 3; // number of 8‑unit groups
    if (fullBlocks > 0) {
        uint32_t *end = buffer + fullBlocks * 32;
        do {
            // Unrolled fill of 32 consecutive dwords (offsets +0x00..+0x1f)
            buffer[0] = fillValue;
            buffer[1] = fillValue;
            buffer[2] = fillValue;
            buffer[3] = fillValue;
            buffer[4] = fillValue;
            buffer[5] = fillValue;
            buffer[6] = fillValue;
            buffer[7] = fillValue;
            buffer[8] = fillValue;
            buffer[9] = fillValue;
            buffer[10] = fillValue;
            buffer[11] = fillValue;
            buffer[12] = fillValue;
            buffer[13] = fillValue;
            buffer[14] = fillValue;
            buffer[15] = fillValue;
            buffer[16] = fillValue;
            buffer[17] = fillValue;
            buffer[18] = fillValue;
            buffer[19] = fillValue;
            buffer[20] = fillValue;
            buffer[21] = fillValue;
            buffer[22] = fillValue;
            buffer[23] = fillValue;
            buffer[24] = fillValue;
            buffer[25] = fillValue;
            buffer[26] = fillValue;
            buffer[27] = fillValue;
            buffer[28] = fillValue;
            buffer[29] = fillValue;
            buffer[30] = fillValue;
            buffer[31] = fillValue;
            buffer += 32;
            fullBlocks--;
        } while (fullBlocks > 0);
    }

    // Remaining dwords (mod 8)
    int32_t remainder = elementCount & 7;
    if (remainder != 0) {
        do {
            *buffer = fillValue;
            buffer++;
            remainder--;
        } while (remainder > 0);
    }
}