// FUNC_NAME: sendEventToManager
void __fastcall sendEventToManager(void* unused, void* obj, uint32_t param3, uint16_t eventType, uint32_t param5, void* data, uint16_t flags)
{
    // Wrapper that calls the actual event posting function with default zero parameters and a global manager pointer.
    // Parameters:
    //   obj - target object (likely a game entity)
    //   eventType - 16-bit event identifier
    //   data - optional data pointer
    //   flags - 16-bit flags
    // The three zero parameters are likely delay, priority, and another flag.
    // DAT_00e2b1a4 is a global pointer to the event manager (e.g., EventScheduler singleton).
    FUN_00572ac0(obj, eventType, data, flags, 0, 0, 0, DAT_00e2b1a4);
}