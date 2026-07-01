// FUNC_NAME: Objective::updateTimer
void __fastcall Objective::updateTimer(Objective* this) {
    // Get audio system pointer from global audio manager (DAT_01129814 + 0x14)
    AudioSystem* audioSys = *(AudioSystem**)(gAudioManager + 0x14);
    
    // Check if timer (offset +0x8C) has reached the threshold
    if (gTimerThreshold <= *(float*)(this + 0x8C)) {
        // Check flag bit 2 at offset +0x90
        if (((*(uint*)(this + 0x90) >> 2) & 1) != 0) {
            // Check if a specific dialog is currently playing (event ID from global)
            if (isDialogPlaying(audioSys, gDialogEventID, 2)) {
                // Stop the dialog
                stopDialog(audioSys, gDialogEventID);
                // Set state to 5 (e.g., "completed" or "triggered")
                *(int*)(this + 0x84) = 5;
                // If there is a vtable pointer at +0x98, call virtual function at offset 0x10
                if (*(void***)(this + 0x98) != nullptr) {
                    (**(code**)(**(int**)(this + 0x98) + 0x10))();
                    return;
                }
            }
        }
    } else {
        // Increment timer by delta (global frame increment)
        float newTimer = *(float*)(this + 0x8C) + gTimerDelta;
        *(float*)(this + 0x8C) = newTimer;
        // If timer now exceeds threshold, stop dialog and signal completion
        if (gTimerThreshold <= newTimer) {
            stopDialog(audioSys, gDialogEventID);
            setMissionComplete(1);
            return;
        }
    }
    return;
}