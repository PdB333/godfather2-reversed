// FUNC_NAME: GeneralUpdateTimer::tick
// Address: 0x009995e0
// Role: Timer update with random delay, called each frame with delta time.
// Fields:
//   +0x0c: pointer to another object with vtable (used for conditions)
//   +0x20: pointer to some state/context (non-null to enable timer)
//   +0x4c: flags (bit 0x100 = disable, bit 0x10 = timer active)
//   +0xa0: start time or timer duration (float)
//   +0xa4: end time or remaining? (float)
// Called functions:
//   FUN_007f47a0 (0x007f47a0) - condition check
//   FUN_0045fad0 (0x0045fad0) - returns current game time (float10)
//   FUN_00995df0 (0x00995df0) - initializes timer with given variable address
//   FUN_00999470 (0x00999470) - final step of timer logic

void __thiscall GeneralUpdateTimer::tick(int thisPtr, float deltaTime)
{
    uint flags = *(uint *)(thisPtr + 0x4c);
    // Check if timer is disabled (bit 8)
    if ((flags & 0x100) != 0) {
        return;
    }

    // Check condition via vtable call (hash 0x55859efa)
    int vtablePtr = *(int *)(thisPtr + 0x0c);
    int (__thiscall *condFunc)(int, uint) = *(int (__thiscall **)(int, uint))(*(int *)vtablePtr + 0x10);
    char conditionResult = condFunc(vtablePtr, 0x55859efa);
    if (conditionResult != '\0') {
        // Another condition check – if it returns 0, we must return early
        char extraCheck = FUN_007f47a0();
        if (extraCheck == '\0') {
            return;
        }
    }

    // Timer logic only if target pointer is non-null
    int *target = *(int **)(thisPtr + 0x20);
    if (target == nullptr) {
        return;
    }

    // 'timer' is a local variable (float) that holds the remaining time
    // Decompiler used 'unaff_retaddr' for it, but it's actually a stack variable
    float timer; // placeholder, but likely passed by reference to sub functions
    // Actually the decompiler used &stack0x00000000, so timer is a local float.
    // We'll assume it's initialized elsewhere; here we use it directly.
    // Since the code compares &stack0x00000000 to DAT_00000004 (likely a constant 4),
    // we treat this as a check that the variable is a valid local.
    // For reconstruction, we assume timer holds the previous remaining time.

    // If timer < 0 (indicating not yet started?), compute new remaining time
    if (timer < 0.0f) {
        float currentTime = (float)FUN_0045fad0();
        float newTimer = currentTime - deltaTime; // - 0.0 omitted
        timer = newTimer;
        if (newTimer < 0.0f) {
            timer = 0.0f;
        }
    }

    int randomVal = _rand();
    float randomFactor = (float)randomVal * DAT_00e44590; // DAT_00e44590 = 1/32767 or similar

    // If timer active flag (bit 4) not set, initialize the timer
    if ((*(uint *)(thisPtr + 0x4c) & 0x10) == 0) {
        FUN_00995df0(&timer); // pass address of local timer
    }

    // Set timer active flag
    *(uint *)(thisPtr + 0x4c) |= 0x10;

    float duration = DAT_01205228 + randomFactor * timer; // base + random * current timer
    *(float *)(thisPtr + 0xa0) = duration;
    *(float *)(thisPtr + 0xa4) = duration + deltaTime;

    FUN_00999470();

    return;
}