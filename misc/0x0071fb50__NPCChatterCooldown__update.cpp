// FUNC_NAME: NPCChatterCooldown::update
void __thiscall NPCChatterCooldown::update(int this, float deltaTime)
{
    char isPaused;
    char isGameActive;
    int randomInt;
    
    // Check if bit 5 of flags is set (m_flags & 0x20)
    if ((*(uint32_t *)(this + 0x20) >> 5 & 1) != 0) 
    {
        // Decrement cooldown timer
        float newTimer = *(float *)(this + 0x10) - deltaTime;
        *(float *)(this + 0x10) = newTimer;
        
        // If timer expired OR (game is paused AND game is not active)
        if (newTimer <= 0.0f || 
            ((isPaused = FUN_0045f120(), isPaused != 0) && 
             (isGameActive = FUN_0045eef0(), isGameActive == 0)))
        {
            // Generate random new cooldown time
            randomInt = _rand();
            // Range: (rand * kRandomScale * kCooldownRange) + kMinCooldown
            *(float *)(this + 0x10) = (float)randomInt * DAT_00e44590 * _DAT_00d5c458 + _DAT_00d5780c;
            
            // Check if NPC can play chatter (via external function)
            char canPlay = FUN_0071f2c0();
            if (canPlay != 0 && ((*(uint32_t *)(this + 0x20) >> 3 & 1) != 0))
            {
                // If a sound is currently playing (m_someId != 0), just return after playing?
                if (*(int *)(this + 4) != 0)
                {
                    FUN_007f63e0(); // Play chatter sound
                    return;
                }
                FUN_007f63e0(); // Play chatter sound
                return;
            }
        }
    }
    return;
}