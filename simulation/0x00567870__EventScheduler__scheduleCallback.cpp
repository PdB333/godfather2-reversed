// FUNC_NAME: EventScheduler::scheduleCallback
void __thiscall EventScheduler::scheduleCallback(void* this, uint targetOrReceiver, uint userData, uint lowPart, uint highPart)
{
    // Store user context for callback
    uint extraParam = userData; // +0x00? unused in this function

    // Combine two 32-bit values into 64-bit parameter (maybe callback ID or data)
    uint64 combinedParam = ((uint64)highPart << 32) | lowPart; // +0x10

    // Fixed callback function defined at LAB_00567930 (hardcoded pointer)
    void (*callbackFunc)(void) = reinterpret_cast<void(*)(void)>(0x00567930); // +0x18

    // Call virtual method at vtable offset 8 (setTimer or scheduleEvent)
    // This sets a timer to invoke targetOrReceiver->callbackFunc with extraParam after 120000ms (2 minutes)
    (*(void(__thiscall**)(void*, void**, uint, int))(*static_cast<int*>(this) + 8))
        (targetOrReceiver, &callbackFunc, 0, 120000);
}