// FUNC_NAME: Player::getEffectiveMaxHealth
int Player::getEffectiveMaxHealth() // __thiscall, this in ECX
{
    int baseStat = *(int *)(this + 0x368); // m_maxHealth (base maximum health)
    // If global bonus pointer (g_gameManager + 0x24f8) is set and the local flag is 1, add 100 health bonus
    if (*(int *)(g_gameManager + 0x24f8) != 0 && *(char *)(this + 0x1aa == 1)) // m_healthBonusFlag
    {
        baseStat += 100;
    }

    bool cheatsEnabled = FUN_008a4380(); // isCheatModeActive? (global toggle)
    // If cheats are on OR the global invulnerability flag at g_gameManager+0x249f bit 0 is 0, return the computed stat.
    // Otherwise return 1 (e.g., minimum possible value)
    if (cheatsEnabled || (*(byte *)(g_gameManager + 0x249f) & 1) == 0) // bit 0 of m_flags
    {
        return baseStat;
    }
    else
    {
        return 1;
    }
}