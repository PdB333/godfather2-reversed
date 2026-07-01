//FUNC_NAME: Player::updateState
void __thiscall Player::updateState(int this) {
    // Call base class update (FUN_004719a0)
    BaseEntity::update();

    // Check if byte at +0x162 is zero (likely "disabled" flag) and bit 2 of uint at +0xc88 is set (some state flag)
    if (*(char *)(this + 0x162) == '\0' && (*(uint *)(this + 0xc88) >> 2 & 1) != 0) {
        // Trigger action with parameter 1 (FUN_0087f950)
        setActionFlag(1);
    }
}