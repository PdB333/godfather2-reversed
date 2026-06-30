// FUNC_NAME: MemoryStream::readU32
// Address: 0x005d2f70
// Reads a 32-bit unsigned integer from the internal buffer at the current offset.
// Structure offsets: +0x00 = m_buffer (uint8_t*), +0x10 = m_offset (int32_t)

uint32_t __thiscall MemoryStream::readU32() {
    uint32_t value = *(uint32_t*)(m_buffer + m_offset);
    m_offset += 4;
    return value;
}