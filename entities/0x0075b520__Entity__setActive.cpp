// FUNC_NAME: Entity::setActive
// Address: 0x0075b520
// Role: Sets or clears bit 3 (0x8) of the uint32 flags field at offset 0x80.
void __thiscall Entity::setActive(bool active) // param_2 treated as bool
{
    if (active) {
        *(uint32_t *)(this + 0x80) |= 8;   // +0x80: flags - set bit 3 (active flag)
    } else {
        *(uint32_t *)(this + 0x80) &= ~8;  // clear bit 3
    }
}