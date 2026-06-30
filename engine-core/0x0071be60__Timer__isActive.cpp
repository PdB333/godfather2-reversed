// FUNC_NAME: Timer::isActive
bool __fastcall Timer::isActive(void* thisPtr)
{
    // Global game time variable at 0x00d577a0 (likely g_currentTime)
    float currentTime = *(float*)0x00d577a0;
    // Offset +0x1C: deadline or expiration time field
    float deadline = *(float*)((int)thisPtr + 0x1C);
    return currentTime <= deadline; // Returns true if current time is within the valid range
}