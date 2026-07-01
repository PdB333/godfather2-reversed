// FUNC_NAME: Player::isInCombatOrAiming
bool __fastcall Player::isInCombatOrAiming(int this)
{
    bool result = false;
    // Check combat state flag at +0x8e8 bit 2 (combat active)
    // Check aiming state flag at +0x8e0 bit 9 (aiming)
    if (((*(uint *)(*(int *)(this + 0x58) + 0x8e8) >> 2 & 1) != 0) ||
        ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 9 & 1) != 0)) {
        result = true;
    }
    return result;
}