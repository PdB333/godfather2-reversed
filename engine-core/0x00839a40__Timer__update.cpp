// FUNC_NAME: Timer::update
// Function address: 0x00839a40
// Role: Advances timer state, checks for completion, and triggers callback.

// Global time scaling factors (likely frame time and speed multiplier)
extern float gFrameTime;       // DAT_01206800
extern float gTimeScale;       // DAT_00d60d04

// Forward declaration of completion callback
void __thiscall Timer::onTimerComplete(void);

void __thiscall Timer::update(void)
{
    // Check if timer is in "running" state (state == 2)
    if (*(int*)(this + 0xe4) == 2) // +0xe4: mState (0=stopped, 1=paused, 2=running)
    {
        // Compute time delta: round(gFrameTime * gTimeScale)
        int delta = (int)(gFrameTime * gTimeScale + 0.5f); // ROUND to nearest int
        *(int*)(this + 0xec) += delta; // +0xec: mElapsed (accumulated time)
    }

    uint duration = *(uint*)(this + 0x8c); // +0x8c: mDuration (threshold)
    if ((duration != 0) && (duration <= *(uint*)(this + 0xec)))
    {
        // Timer completed: reset elapsed and fire callback
        *(uint*)(this + 0xec) = duration; // Clamp to duration (optional)
        Timer::onTimerComplete();
    }
}