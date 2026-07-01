// FUNC_NAME: Entity::updateCooldownTimer
// Address: 0x008f8260
// Role: Updates a cooldown timer by subtracting a delta value, clamping to a global maximum if below threshold.
// Fields: +0x164 (float timer), +0x18c (float subtractValue), +0x170 (uint flags)

void __fastcall Entity::updateCooldownTimer(Entity* thisObj)
{
    float maxCooldown = DAT_00d58cbc; // global constant (e.g., max cooldown time)
    uint flags = *(uint*)(thisObj + 0x170);

    // Check if bit 1 is set (cooldown active) and bit 7 is clear (not paused)
    if (((flags >> 1) & 1) != 0 && ((flags >> 7) & 1) == 0)
    {
        float timer = *(float*)(thisObj + 0x164);
        float subtract = *(float*)(thisObj + 0x18c); // e.g., delta time
        float newTimer = timer - subtract;
        bool belowThreshold = newTimer <= maxCooldown;

        *(float*)(thisObj + 0x164) = newTimer;

        if (belowThreshold)
        {
            // Reset timer to max cooldown (or clamp)
            *(float*)(thisObj + 0x164) = maxCooldown;
        }
    }
}