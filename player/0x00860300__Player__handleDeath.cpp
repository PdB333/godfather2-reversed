// FUNC_NAME: Player::handleDeath
void Player::handleDeath(bool isInstantDeath)
{
    FUN_00875d10(this);
    int iVar1 = FUN_00542d70();
    if (iVar1 != 0) {
        if (isInstantDeath) {
            FUN_0086d060(2, 1);
            return;
        }
        FUN_0086d060(0, 1);
    }
    return;
}