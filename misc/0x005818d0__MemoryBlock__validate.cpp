// FUNC_NAME: MemoryBlock::validate
bool MemoryBlock::validate() const {
    // Check first byte (type/class ID) < 0x23
    if (m_byte0 >= 0x23) return false;

    // Check second byte (subtype?) in range [1, 7]
    uint8_t subtype = m_byte1;
    if (subtype <= 0 || subtype >= 8) return false;

    // Check short field at +0x2: must be in [0, 0x80)
    int16_t flags = m_flags;
    if (flags < 0 || flags >= 0x80) return false;

    // Check pointer at +0xC must point within this block's buffer (0x200 bytes)
    uint8_t* ptr = m_nextBlock; // pointer to next block or free list
    if (ptr < (uint8_t*)this || ptr >= (uint8_t*)this + 0x200) return false;

    return true;
}