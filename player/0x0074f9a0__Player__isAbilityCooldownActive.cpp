// FUNC_NAME: Player::isAbilityCooldownActive
bool __fastcall Player::isAbilityCooldownActive()
{
    PlayerState* pPlayerState = *(PlayerState**)((uint)this + 0x110); // m_pPlayerState
    if (!FUN_00716330()) // isGameActive
    {
        return false;
    }
    PlayerManager* pPlayerManager = (PlayerManager*)FUN_00800a90(); // PlayerManager::getInstance
    if (pPlayerManager == nullptr)
    {
        return false;
    }
    int cooldownStart = *(int*)((uint)pPlayerState + 0x24bc); // PlayerState::m_cooldownStartTime
    float currentTime = FUN_00701050(); // getCurrentTimeInSeconds
    float startFloat = (float)cooldownStart;
    if (cooldownStart < 0)
    {
        startFloat += *(float*)0x0e44578; // DAT_00e44578: 4294967296.0f (unsigned int conversion)
    }
    startFloat *= *(float*)0x0d5efb8; // DAT_00d5efb8: scale factor (possibly ms->s)
    float remaining = *(float*)0x1205228 - startFloat; // DAT_01205228: max cooldown duration
    float timeDelta = FUN_007159b0(currentTime); // compareTime: returns 0.0f or a small delta
    if (!(timeDelta < remaining)) // if cooldown expired, return false
    {
        return false;
    }
    // Cooldown still active, check if input or menu blocks action
    bool blocked = false;
    if (pPlayerManager != nullptr && *(int*)((uint)pPlayerManager + 0x328) == 0) // m_bIsInputBlocked
    {
        blocked = true;
    }
    return !blocked; // returns true only when input is blocked while on cooldown
}