// FUNC_NAME: Entity::setActive
void __thiscall Entity::setActive(void) {
    *(uint8_t *)(this + 0x150) = 1; // +0x150: activeFlag (bool, 1=active)
}