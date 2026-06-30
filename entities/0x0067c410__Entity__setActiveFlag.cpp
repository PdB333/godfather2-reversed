// FUNC_NAME: Entity::setActiveFlag
void __thiscall Entity::setActiveFlag(void *this) {
    // Set byte at +0x08 to 1 (active/enabled flag)
    *(uint8_t *)((int)this + 8) = 1;
}