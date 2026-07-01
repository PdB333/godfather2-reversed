// FUNC_NAME: PlayerViewManager::onFocusGained
void __thiscall PlayerViewManager::onFocusGained() {
    // Check if sub-controller (e.g., input device or camera controller) exists
    if (this->subController != nullptr) {
        // Enable input processing (1 = focus gained)
        setInputFocus(1);

        // Update camera system to match this view
        updateCamera(this);

        // Perform global engine tick (e.g., audio, physics)
        globalTick();

        // Reset certain game state flags (parameter: type, state, something)
        resetGameState(0, 1, 0);

        // Set viewport/window association for this manager
        setViewport(this, 1);

        // Mark sub-controller flags: enable invert Y (offset 0x5E1) and vibration (offset 0x5E3)
        this->subController->enableInvertY = 1;      // +0x5E1
        this->subController->enableVibration = 1;    // +0x5E3

        // Clear low 4 bits of state flags and set bits for active + something (0x14 = 0b10100)
        this->stateFlags = (this->stateFlags & 0xFFFFFFF0) | 0x14; // +0x81C

        // Assign global screen ID to this view
        this->currentScreenId = g_ScreenId; // +0x79C

        // Finalize view setup (e.g., apply resolution, UI refresh)
        finalizeViewSetup();
    }
}