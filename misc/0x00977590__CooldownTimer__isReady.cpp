// FUNC_NAME: CooldownTimer::isReady
bool __fastcall CooldownTimer::isReady(int this) const
{
    // Check if cooldown is active. Offset +0x18 stores the cooldown end timestamp.
    uint cooldownEnd = *(uint *)(this + 0x18);
    if (cooldownEnd != 0) {
        // Get current time (likely from engine timer).
        uint currentTime = getCurrentTime();
        // If current time is less than cooldown end, action is not ready.
        if (currentTime < cooldownEnd) {
            return false;
        }
    }
    // No cooldown or cooldown expired.
    return true;
}