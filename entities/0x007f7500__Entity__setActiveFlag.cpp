// FUNC_NAME: Entity::setActiveFlag
/**
 * Address: 0x007f7500
 * Role: Sets a boolean flag at offset 0xA31 (presumably "active" or "inUse") to true.
 * Called from: FUN_007abec0
 */
void __thiscall Entity::setActiveFlag(void) {
    *(uint8_t *)(this + 0xA31) = 1;
}