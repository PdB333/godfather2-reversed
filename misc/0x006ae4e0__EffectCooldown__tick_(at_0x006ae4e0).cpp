// FUNC_NAME: EffectCooldown::tick (at 0x006ae4e0)
// Decompiled reconstruction of effect cooldown update logic.
// The object at `this` contains:
//   +0x188: float currentDecayValue  (clamped by global threshold)
//   +0x18c: float timerRemaining       (cooldown countdown)
//   +0x2b4: uint8 flags               (bit 1 = active flag)
// Global constants:
//   DAT_012067e8 = delta time (e.g., frame time)
//   _DAT_00d577a0 = decay threshold
//   _DAT_00d5780c = reset value for timer (e.g., cooldown duration)
//   DAT_0112ad8c = string literal for logging/event name

void __fastcall EffectCooldown::tick(EffectCooldown* this)
{
    float deltaTime = DAT_012067e8; // game frame delta
    uint8 flags = *(uint8*)((int)this + 0x2b4);

    // Decay a value towards zero, clamped by global threshold
    float* decayVal = (float*)((int)this + 0x188);
    if (_DAT_00d577a0 < *decayVal)
    {
        *decayVal -= deltaTime;
    }

    // Only process cooldown if bit 1 of flags is set
    if ((flags & 2) != 0)
    {
        int gameState = FUN_006b4860(); // likely returns current game mode
        if ((gameState != 4) && (gameState != 3))
        {
            // Not in the correct game state, clear the active flag and exit
            *(uint8*)((int)this + 0x2b4) &= 0xfd; // clear bit 1
            return;
        }

        // Decrease timer by delta time
        float* timer = (float*)((int)this + 0x18c);
        *timer -= deltaTime;

        if (*timer <= 0.0f)
        {
            // Timer expired: reset it and trigger effect/event
            *(float*)((int)this + 0x18c) = _DAT_00d5780c; // reset to cooldown duration

            // Call function with an event hash (likely spawn effect, play sound, etc.)
            FUN_006ada80(this, 0x4e76981c); // hash for "effect_cooldown_trigger" or similar

            // Build a temporary string for logging or event parameter
            undefined4 local_30;
            undefined1* local_2c;
            undefined1 local_28;
            undefined1 local_24[8];
            int local_1c[7];

            local_30 = DAT_0112ad8c;       // string literal
            local_28 = 0;
            local_2c = local_24;           // buffer for string manipulation
            FUN_00408a00(&local_30, 0);    // possibly initialize FastString

            if (local_1c[0] != 0)
            {
                FUN_004daf90(local_1c);    // release string resource
            }
        }
    }
}