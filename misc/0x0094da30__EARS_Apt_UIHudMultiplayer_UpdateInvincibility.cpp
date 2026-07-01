// Xbox PDB: EARS_Apt_UIHudMultiplayer_UpdateInvincibility
// FUNC_NAME: Player::setInvincibility
void __thiscall Player::setInvincibility(char enable)
{
    // Check: object is active (offset 0x48), not blocked by status flags (offset 0x49: bits 0x0A = 10 = invincibility block?), and not already in requested state (offset 0xBA)
    if (*(char *)(this + 0x48) != '\0' && (*(byte *)(this + 0x49) & 0x0A) == 0 && *(char *)(this + 0xBA) != enable)
    {
        const char *message = "StartInvincibility";
        if (enable == '\0')
        {
            message = "StopInvincibility";
        }
        // Notify underlying systems (logging/script event)
        notifyInvincibilityChange(message, 0, &gInvincibilityNotifyContext, 0);
        // Store new invincibility state
        *(char *)(this + 0xBA) = enable;
    }
}