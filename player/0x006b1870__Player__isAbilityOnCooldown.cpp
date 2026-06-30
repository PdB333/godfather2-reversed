// FUNC_NAME: Player::isAbilityOnCooldown
// Function address: 0x006b1870
// Checks whether an ability (or action) is still on cooldown.
// Uses a flag bit and a timestamp compared with global game time.

bool __thiscall Player::isAbilityOnCooldown()
{
    // +0x34: flags (uint), bit 27 indicates cooldown active
    // +0x70: cooldown start time (int)
    // DAT_01205224: g_gameTime (global game tick count)
    if (((*(uint *)(this + 0x34) >> 0x1b & 1) != 0) &&
        (g_gameTime < *(int *)(this + 0x70) + 30000U))
    {
        return true;
    }
    return false;
}