// FUNC_NAME: Entity::setActive @ 0x00721350
// Sets or clears bit 0 of the flags at offset 0x0C (active flag)
void __thiscall Entity::setActive(bool active)
{
    if (active) {
        *(uint32_t *)(this + 0x0C) |= 1;   // set bit 0
    } else {
        *(uint32_t *)(this + 0x0C) &= ~1;  // clear bit 0
    }
}