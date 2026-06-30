// FUNC_NAME: ControllerManager::processStartButton
void __thiscall ControllerManager::processStartButton(int this) {
    char cVar1;
    uint uVar2;
    SoundEvent localSound;
    // +0x14: m_triggerSlot (byte, 0x13 means any slot)
    if (*(char*)(this + 0x14) == 0x13) {
        // Check all controller slots for a specific button press (mask = 0x1000, mode = 2)
        uVar2 = 0;
        do {
            cVar1 = IsButtonDown((char)uVar2, 0x1000, 2);
            if (cVar1 != '\0') {
                HandleStartButtonActivation((char)uVar2);
                break;
            }
            uVar2 = uVar2 + 1;
        } while (uVar2 < 0x10);
    } else {
        // Specific slot given
        cVar1 = IsButtonDown(*(char*)(this + 0x14), 0x1000, 2);
        if (cVar1 != '\0') {
            *(int*)(this + 0x10) = 2; // +0x10: m_pressState
        }
    }
    if (*(int*)(this + 0x10) == 2) {
        // Clear the button state
        ClearButtonInput(*(char*)(this + 0x14), 0x1000); // actually takes byte and mask
        if (g_bInMenu != 0) { // global pause flag
            ShowPauseMenu(0, 0, 0);
        }
        localSound = g_someSoundId; // global sound ID
        // localSound is a struct; second parameter 0
        PlaySoundEffect(&localSound, 0);
    }
}