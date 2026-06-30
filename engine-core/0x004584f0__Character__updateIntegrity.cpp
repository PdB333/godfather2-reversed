// FUNC_NAME: Character::updateIntegrity
void __thiscall Character::updateIntegrity(float healthDelta, float shieldDelta)
{
    // +0xe0: bool isDead (or similar)
    if (*(char *)(this + 0xe0) == '\0') {
        // DAT_00e44598 = max shield threshold that triggers hit FX
        if ((shieldDelta < DAT_00e44598) && (DAT_01143360 != 0)) {
            // +0xd8: handle for hit sound/effect
            FUN_005ddaf0(*(undefined4 *)(this + 0xd8));
            float fVar2 = 0.0f;
            if ((0.0f < healthDelta) && (fVar2 = DAT_00e2b1a4, healthDelta < DAT_00e2b1a4)) {
                fVar2 = healthDelta;
            }
            // Render hit feedback (particle or decal)
            FUN_00c9cbe0(DAT_01143360, *(undefined4 *)(*(int *)(*(int *)(this + 0xc0) + 4) + 0x10), 0, &local_24);
            local_24 = 0;
            local_1c = 0;
            local_c = 0;
            local_14 = fVar2 * DAT_00e2b1a4;
            FUN_00c9eac0();  // Begin rendering batch
            FUN_00c9cd40(0, &local_24);
            FUN_00c9eae0();  // End rendering batch
            // +0xe8: some state (e.g., last hit timestamp)
            *(undefined4 *)(this + 0xe8) = unaff_ESI; // likely a time or trigger ID
        }
        // Protect healthDelta, clamp to [0, DAT_00e2b1a4]
        float clampedHealth = 0.0f;
        if (0.0f < healthDelta) {
            clampedHealth = healthDelta;
            if (healthDelta < DAT_00e2b1a4) {
                clampedHealth = healthDelta;
            } else {
                clampedHealth = DAT_00e2b1a4;
            }
        } else {
            clampedHealth = 0.0f;
        }
        *(float *)(this + 0xec) = clampedHealth;  // +0xec: current health (or health delta)
        // Protect shieldDelta, clamp to [0, DAT_00e4458c]
        if (shieldDelta <= 0.0f) {
            *(float *)(this + 0xf0) = 0.0f;       // +0xf0: current shield (or shield delta)
            return;
        }
        float clampedShield = shieldDelta;
        if (shieldDelta < DAT_00e4458c) {
            clampedShield = shieldDelta;
        } else {
            clampedShield = DAT_00e4458c;
        }
        *(float *)(this + 0xf0) = clampedShield;
    }
    return;
}