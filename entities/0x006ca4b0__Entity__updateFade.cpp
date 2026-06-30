// FUNC_NAME: Entity::updateFade

// Updates a smoothed fade value (byte target at +0x7C, float current at +0x80)
// based on a settings flag and global game state.
void __thiscall Entity::updateFade(int this, int* pSettings, float dt)
{
    byte target;
    bool shouldBeVisible;

    // Query a virtual function on pSettings (hash 0x55859efa likely a boolean setting)
    shouldBeVisible = (**(code (__thiscall **)(int*, uint))(*pSettings + 0x10))(pSettings, 0x55859efa) != '\0';

    if (shouldBeVisible)
    {
        // Call a global function pointer (likely IsGameActive or similar)
        bool gameActive = ((byte (*)(void))g_isGameActiveFunc)() != '\0';
        if (gameActive)
        {
            target = 1;
        }
        else
        {
            target = 0;
        }
    }
    else
    {
        target = 0;
    }

    // Write the target state
    *(byte *)(this + 0x7C) = target;

    // Check for "force immediate" condition (global pointer to player state)
    int** ppPlayerArray = *(int***)(g_globalData + 4);
    int* pPlayer = *ppPlayerArray;
    if (pPlayer != 0 && pPlayer != (int*)0x1F30 && (*(uint*)(pPlayer + 0x56C) & 0x20) != 0)
    {
        // Force the current fade to the target (no smoothing)
        *(float *)(this + 0x80) = (float)target;
        return;
    }

    // Smooth interpolation (only if some condition holds, likely always true)
    if (*(byte *)(this + 0x7C) == 0)
    {
        // Decrease towards 0
        float newFade = *(float *)(this + 0x80) - dt * g_fadeRate;
        if (newFade < 0.0f) newFade = 0.0f;
        *(float *)(this + 0x80) = newFade;
    }
    else
    {
        // Increase towards 1 (clamped to g_maxFade)
        float newFade = *(float *)(this + 0x80) + dt * g_fadeRate;
        if (newFade > g_maxFade) newFade = g_maxFade;
        *(float *)(this + 0x80) = newFade;
    }
}