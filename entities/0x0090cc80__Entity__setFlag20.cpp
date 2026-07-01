// FUNC_NAME: Entity::setFlag20
// Sets or clears bit 5 (0x20) in the flags field at offset +0x14.
// @param enable: true to set the bit, false to clear it.
void __thiscall Entity::setFlag20(bool enable) {
    // uint32_t m_flags at +0x14
    if (enable) {
        this->m_flags |= 0x20; // set bit 5
    } else {
        this->m_flags &= ~0x20; // clear bit 5
    }
}