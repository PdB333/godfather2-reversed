// FUNC_NAME: Player::updateCooldownTimer
// Address: 0x007d4110
// Decrements a per-player timer at this+0xC0 each frame.
// When timer expires and the ability flag (this+0x58) is set, notifies the game manager.
void __thiscall Player::updateCooldownTimer(float deltaTime)
{
    float &timer = *(float *)(this + 0xC0);               // +0xC0: cooldown timer (seconds)
    timer -= deltaTime;

    if (timer < 0.0f && *(int *)(this + 0x58) != 0)      // +0x58: ability active flag (bool)
    {
        // Retrieve the GodfatherGameManager singleton (type unknown, vtable at offset 0x28 for message dispatch)
        void *manager = (void *)FUN_0043b870(DAT_01130fa0);
        if (manager != nullptr)
        {
            // Check that the game is in a valid state (player exists, alive, etc.)
            uint gameTime = FUN_009a9520();               // returns something like current game time or player ID
            if (gameTime != 0 && FUN_007ff880() != 0)    // likely IsPlayerAlive() / IsGameActive()
            {
                if (DAT_0112a9c0 == 0)                   // global debug flag (0 = normal, 1 = skip messages)
                {
                    // Send a message to the manager with ID 0xfe329ece (e.g., "AbilityCooldownExpired")
                    // signature: (uint msgID, int param1, int param2, int param3)
                    (*(void (__thiscall **)(void *, uint, int, int, int))(*(int *)manager + 0x28))
                        (manager, 0xfe329ece, 1, 0xffffffff, 0);
                }
                else
                {
                    // Debug mode: additional validation (e.g., CanSendMessageForPlayer)
                    if (FUN_006eaba0(gameTime) == '\0')
                        return;
                }
                // Reset the timer to a global default value (DAT_00d6ef28 defines the cooldown duration)
                *(float *)(this + 0xC0) = DAT_00d6ef28;
            }
        }
    }
}