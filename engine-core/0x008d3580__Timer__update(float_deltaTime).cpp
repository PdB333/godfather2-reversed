// FUNC_NAME: Timer::update(float deltaTime)
void __thiscall Timer::update(float deltaTime)
{
    // Add delta time to current elapsed time at offset +0x10
    float curTime = *(float *)(this + 0x10) + deltaTime;
    *(float *)(this + 0x10) = curTime;

    // If elapsed time >= threshold (+0x14) and global flag (g_pauseTimer or similar) is less than threshold
    float threshold = *(float *)(this + 0x14);
    if (threshold <= curTime && *(float *)0x00e44598 < threshold)
    {
        // Trigger timer callback (likely starts or fires event)
        FUN_008d33e0();

        // Build a 12-byte event data structure (GUID? Message?)
        // Using DAT_0112f9d0 as the first field, 0 for the others
        struct EventData {
            uint32_t field0; // +0x00
            uint32_t field4; // +0x04
            uint8_t  field8; // +0x08
        } eventData;
        eventData.field0 = *(uint32_t *)0x0112f9d0;
        eventData.field4 = 0;
        eventData.field8 = 0;

        // Send the event (e.g., EventManager::postEvent)
        FUN_00408a00(&eventData, 0);

        // Finalize timer (reset or stop)
        FUN_008d3340();

        // Reset elapsed time
        *(float *)(this + 0x10) = 0.0f;
    }
}