// Xbox PDB: EARS_Apt_UIHud_UpdatePressureMeter
// FUNC_NAME: PlayerPressureManager::handleEvent
void __thiscall PlayerPressureManager::handleEvent(int eventType, void* eventData, float pressureValue)
{
    // Check if pressure system is active (bit 9 of flags at +0x5c)
    if ((*(uint*)(this + 0x5C) >> 9 & 1) == 0)
        return;

    // Determine the target ID from the attached entity (if any)
    int targetId;
    if (*(int*)(this + 0x114) == 0)
        targetId = 0;
    else
        targetId = *(int*)(this + 0x114) - 0x48; // offset for type

    // Ignore events that don't match current target
    if (targetId != eventType)
        return;

    // Save the raw value from event data (e.g., damage or pressure amount)
    *(float*)(this + 0x12C) = *(float*)((char*)eventData + 0x40);

    // Clear the message buffer (first byte of string at +0x130)
    **(char**)(this + 0x130) = 0;

    // Check if this is a "victory" event (e.g., from a QTE success)
    bool isVictory = FUN_0078b010();
    if (!isVictory)
    {
        // Check if this is a job success event
        bool isJobSuccess = FUN_0078af40();
        if (isJobSuccess)
        {
            // Event type must have specific flags (0x10C = combo damage?)
            if ((*(uint*)(eventType + 0x1F98) & 0x10C) == 0)
                return;

            // Cooldown check (global threshold vs. local timer)
            if (DAT_01205224 <= *(uint*)(this + 0x138))
                return;

            // Retrieve localized job success string
            uint32_t stringId = FUN_00737710(); // returns a string ID
            char* strPtr = nullptr;
            uint32_t dummy1 = 0, dummy2 = 0;
            void (*cleanupFunc)() = nullptr;
            FUN_00604000(stringId, &strPtr, 1);

            const char* sourceStr = strPtr;
            if (strPtr == nullptr)
                sourceStr = &DAT_0120546e; // fallback string

            // Build the HUD message
            FUN_005c4630(*(uint32_t*)(this + 0x130), 0x80, "{$job_success} %s", sourceStr);

            // Update the local timer (add 0xB6 ticks = ~0.8 seconds?)
            *(uint32_t*)(this + 0x138) = DAT_01205224 + 0xB6;

            // Play job success sound
            FUN_00402050(&DAT_011302a0, 0);

            // Update pressure meter UI
            FUN_005a04a0("UpdatePressureMeter", 0, &DAT_00d8a64c, 0);

            // Show weak spot bonus if applicable (bit 0 of event data +0x3C)
            if ((*(uint8_t*)((char*)eventData + 0x3C) & 1) != 0)
            {
                FUN_005a04a0("ShowWeakSpotBonus", 0, &DAT_00d8a64c, 0);
            }

            // Clean up if we allocated a string
            if (strPtr != nullptr)
                cleanupFunc();

            return; // job success ends here
        }
    }
    else
    {
        // Victory event: if the pressure exceeds a global threshold, show a text
        if (DAT_00d5780c < pressureValue)
        {
            FUN_005c4630(*(uint32_t*)(this + 0x130), 0x80, "+%.f {$hud_pressure_pressure}", (double)pressureValue);
            FUN_00402050(&DAT_01130438, 0);
        }
    }

    // Final update for the pressure meter (always runs for pressure/victory cases)
    FUN_005a04a0("UpdatePressureMeter", 0, &DAT_00d8a64c, 0);
}