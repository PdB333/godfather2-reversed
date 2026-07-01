// Xbox PDB: EARS_Apt_UIHud_UpdateWeaponWheel
// FUNC_NAME: PlayerActionableTargetSM::handleWeaponInput
// Address: 0x0093c2a0
// Role: Processes weapon selection input (mapping UI weapon indices to internal states)
// and triggers UI updates for stick XY and weapon selection, then resets a timer
// and updates the weapon display. Flags the object as needing update via setting bit 0x20 at +0x5C.

void __thiscall PlayerActionableTargetSM::handleWeaponInput(void* thisPtr, int weaponIndex)
{
    // +0xD4 appears to be the internal weapon slot or action ID
    // Map from UI weapon indices (7,8,9) to internal IDs (8,6,7)
    if (weaponIndex == 7) {
        *(int*)((char*)thisPtr + 0xD4) = 8;
    } else if (weaponIndex == 8) {
        *(int*)((char*)thisPtr + 0xD4) = 6;
    } else if (weaponIndex == 9) {
        *(int*)((char*)thisPtr + 0xD4) = 7;
    }

    // Check if weapon input is currently allowed (e.g., not in a cutscene)
    if (isWeaponInputAllowed()) {
        // Clear stick XY offsets (used for aiming direction)
        // +0xD8 and +0xDC likely store stick X/Y values
        *(int*)((char*)thisPtr + 0xD8) = 0;
        *(int*)((char*)thisPtr + 0xDC) = 0;

        // Notify UI to update stick XY display
        // Signature: postEvent(const char* eventName, int senderID, const void* data, int dataSize)
        postEvent("UpdateStickXY", 0, (const void*)0, 0);
    }

    // Notify UI that the selected weapon has changed
    postEvent("UpdateWeaponSelected", 0, (const void*)0, 0);

    // Create a timer struct from global timer value (DAT_011303d0)
    // The struct layout: { int time; int zero1; char zero2; } - used for cooldown/timer
    struct TimerInfo {
        int time;      // +0x00
        int zero1;     // +0x04
        char zero2;    // +0x08
    };
    TimerInfo timerInfo;
    timerInfo.time = *(int*)0x011303d0;   // DAT_011303d0 - global game time
    timerInfo.zero1 = 0;
    timerInfo.zero2 = 0;

    // Reset the timer with a zero parameter (possibly a duration, 0 means immediate)
    resetTimer(&timerInfo, 0);

    // Update weapon display or state (e.g., current weapon icon, ammo count)
    updateWeaponDisplay();

    // Set a dirty flag (bit 5) at +0x5C to indicate state has changed
    *(unsigned int*)((char*)thisPtr + 0x5C) |= 0x20;
}