// FUNC_NAME: Player::hasActiveWeaponOrItem
bool __fastcall Player::hasActiveWeaponOrItem(int this) // param_1 = this
{
    // Check if weapon slot (+0x2d8) and item slot (+0x360) are both non-null
    if ((*(int *)(this + 0x2d8) != 0) && (*(int *)(this + 0x360) != 0)) {
        return true;
    }
    return false;
}