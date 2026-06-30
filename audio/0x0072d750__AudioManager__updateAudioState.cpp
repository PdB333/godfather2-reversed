// FUNC_NAME: AudioManager::updateAudioState
// Function address: 0x0072d750
// Role: Determines whether to trigger a sound event based on current state and playing sounds.

void __thiscall AudioManager::updateAudioState(int thisPtr) {
    char cVar1;

    // Check if a sound handle is active (non-null pointer at offset 0x180)
    if (*(int *)(thisPtr + 0x180) == 0) {
        // No active sound handle; check conditions to skip sound trigger
        cVar1 = FUN_007f9fb0(); // Likely: isCutscenePlaying() or isPaused()
        if (cVar1 == '\0') {
            cVar1 = FUN_0054f460(DAT_00d5ef88); // Likely: isPlayerInControl() or similar global state check
            if (((cVar1 != '\0') && ((*(uint *)(thisPtr + 0x8e4) >> 0xb & 1) == 0)) &&
               ((*(uint *)(thisPtr + 0x8e4) >> 10 & 1) == 0)) {
                cVar1 = FUN_00690150(0x48); // Check sound/event ID 0x48
                if (cVar1 == '\0') {
                    cVar1 = FUN_00690150(0x5c); // Check sound/event ID 0x5c
                    if (cVar1 == '\0') {
                        // Neither sound is playing -> return without triggering sound event
                        return;
                    }
                }
            }
        }
    }
    // If we reach here, conditions are met to trigger the sound event
    FUN_007f8bd0(); // Likely: triggerSoundEvent()
}