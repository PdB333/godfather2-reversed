// FUNC_NAME: Entity::activateComponentGroup

void Entity::activateComponentGroup() {
    // +0x4c: uint32 m_flags; bit1 (0x2) = components already activated
    uint32_t& flags = *(uint32_t*)((uint8_t*)this + 0x4c);
    if (!(flags & 2)) {
        // Call the inner activation routine three times (e.g., for three sub‑components)
        activateComponent();
        activateComponent();
        activateComponent();
        flags |= 2;   // Mark as activated
    }
}