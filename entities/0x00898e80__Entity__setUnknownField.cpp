// FUNC_NAME: Entity::setUnknownField
void __thiscall Entity::setUnknownField(uint32_t value) {
    // Store value at offset +0xC4 (likely a pointer or handle)
    *(uint32_t *)(this + 0xC4) = value;
}