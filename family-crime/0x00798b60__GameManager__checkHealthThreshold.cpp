// FUNC_NAME: GameManager::checkHealthThreshold
void __thiscall GameManager::checkHealthThreshold(void)
{
    int statePtr = GetGlobalStateManager();   // Returns singleton with float at +0x34
    // +0x34: tracked value (e.g., health, timer, or progress)
    float currentValue = *(float *)(statePtr + 0x34);
    if (currentValue <= g_fThresholdValue && g_fThresholdValue != currentValue)
    {
        // Virtual function at vtable+0x288 (likely TriggerLowHealth, SetDangerState, etc.)
        // Called with (1, 0) – first arg may be bool, second a flag
        (*(void (__thiscall **)(int, int))(*(int **)this + 0x288 / 4))(1, 0);
    }
}