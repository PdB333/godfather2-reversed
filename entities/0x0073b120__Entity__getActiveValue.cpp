// FUNC_NAME: Entity::getActiveValue
uint32_t __thiscall Entity::getActiveValue(void) {
    // +0xa4: state/type field (0 = invalid, 0x48 = destroyed/inactive)
    // +0xa0: value field (e.g., health, ammo, or other resource)
    uint32_t state = *(uint32_t*)((uint8_t*)this + 0xa4);
    if (state != 0 && state != 0x48) {
        return *(uint32_t*)((uint8_t*)this + 0xa0);
    }
    return 0;
}