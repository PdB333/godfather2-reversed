// FUNC_NAME: PlayerState::isStateDurationWithinRange
bool __fastcall PlayerState::isStateDurationWithinRange(int this)
{
    float currentValue = *(float *)(this + 0x30); // +0x30: some state-related float (e.g., timer, speed, distance)
    // Global thresholds for valid range: g_minBound, g_maxBound, g_toleranceNearMax
    if (g_minBound < currentValue && currentValue <= g_maxBound && (g_maxBound - currentValue) < g_toleranceNearMax)
    {
        return true;
    }
    return false;
}