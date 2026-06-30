// FUNC_NAME: Entity::updateSmoothedValue
void __fastcall Entity::updateSmoothedValue(void* thisPtr)
{
    float smoothFactor = 0.0f;
    float target = 0.0f;

    // Offset +0x78 likely indicates whether smoothing is active
    if (*(int*)((int)thisPtr + 0x78) != 0) {
        smoothFactor = *(float*)((int)thisPtr + 0xa4);  // +0xa4: smoothing acceleration factor
        float dt = (float)FUN_005fe710();               // probably getGameDeltaTime()
        float scaled = dt * smoothFactor;
        target = scaled;
        // +0xe8: bit0 = direction flag (positive/negative)
        if (scaled >= 0.0f) {
            *(uint*)((int)thisPtr + 0xe8) |= 1;
        } else {
            *(uint*)((int)thisPtr + 0xe8) &= 0xfffffffe;
        }
    }

    // +0xd4: current smoothed value
    float current = *(float*)((int)thisPtr + 0xd4);
    float diff = current - target;

    // Mask off sign bit to get absolute value of the difference
    // DAT_00e44680 is 0x7fffffff
    uint absBits = *(uint*)&diff & 0x7fffffff;
    float absDiff = *(float*)&absBits;

    // Apply a dead zone / threshold (DAT_01206800 * _DAT_00d5c458 is a constant epsilon)
    const float kDeadZone = 0.002f; // example value, real constant unknown
    float clampedDiff = absDiff - kDeadZone;
    if (clampedDiff < 0.0f) {
        clampedDiff = 0.0f;
        // +0xe8 bit1: clamp activated flag
        *(uint*)((int)thisPtr + 0xe8) &= 0xfffffffd;
    }

    // Update current value: move toward target, staying at least kDeadZone away
    if (*(uint*)((int)thisPtr + 0xe8) & 1) {
        *(float*)((int)thisPtr + 0xd4) = target - clampedDiff;
    } else {
        *(float*)((int)thisPtr + 0xd4) = target + clampedDiff;
    }
}