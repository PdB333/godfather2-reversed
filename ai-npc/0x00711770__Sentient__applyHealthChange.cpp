// FUNC_NAME: Sentient::applyHealthChange

void __thiscall Sentient::applyHealthChange(float delta)
{
    // Get pointer to sub-object (likely a damage/health component) at offset +0x4
    int subObj = *(int*)(this + 4);

    // Check if health modifications are allowed (bit 7 of flags at subObj+0x21b0)
    if (*(uint*)(subObj + 0x21b0) & 0x80)
    {
        // Randomize the delta using a linear transform of rand()
        int randValue = rand();
        float randomizedDelta = ((float)randValue * g_healthChangeRandomScale + g_healthChangeRandomBase) * delta;

        // If the resulting delta is positive (healing), scale it based on distance from max health
        if (randomizedDelta > 0.0f)
        {
            float maxHealth = g_maxHealth;                               // global max health
            float currentHealth = *(float*)(this + 0x54);                // +0x54 health value
            randomizedDelta = (maxHealth - currentHealth) * randomizedDelta;
        }

        // Apply the (possibly scaled) delta and clamp to zero
        float newHealth = *(float*)(this + 0x54) + randomizedDelta;
        if (newHealth < 0.0f)
        {
            newHealth = 0.0f;
        }
        *(float*)(this + 0x54) = newHealth;
    }
}