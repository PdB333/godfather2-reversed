//FUNC_NAME: Entity::setFlag0x40
// Function at 0x007f62f0 sets bit 6 (0x40) of a flags field at offset 0x970.
// This likely marks some state as dirty or active.

void __thiscall Entity::setFlag0x40(void) {
    // Set bit 6 of m_flags (offset +0x970)
    *(uint32_t*)((uint8_t*)this + 0x970) |= 0x40;
}