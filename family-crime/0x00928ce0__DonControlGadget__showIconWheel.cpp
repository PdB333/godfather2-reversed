// FUNC_NAME: DonControlGadget::showIconWheel
void DonControlGadget::showIconWheel()
{
    // +0x60: some timer or state counter
    *(int *)(this + 0x60) = 0;
    // +0x64: another field (offset 100 decimal)
    *(int *)(this + 0x64) = 0;

    // Call Lua to show the icon wheel (DAT_00d87b2c is the Lua state)
    callLuaFunction("ShowIconWheel", 0, gLuaState, 0);
    // Reset UI animation system?
    resetUIAnimation();

    // Prepare timer parameters (global constant used as initial value)
    int timerParam1 = DAT_01130428;
    int timerParam2 = 0;
    int timerParam3 = 0;
    // Start timer with these parameters
    startTimer(&timerParam1, 0);

    // +0x5c: current selection index or mode (10 means something specific)
    if (*(int *)(this + 0x5c) == 10) {
        // Reset selection and update Lua
        *(int *)(this + 0x5c) = -1;
        callLuaFunction("UpdateIconSelected", 0, gLuaState, 0);
    }

    callLuaFunction("UpdateIconInfo", 0, gLuaState, 0);

    // +0x50: flags (bit0 set to indicate visible)
    *(unsigned int *)(this + 0x50) |= 1;

    // Play animation from a code label (address LAB_00928cd0, probably an animation name entry)
    playAnimation(this + 0x10, &LAB_00928cd0, 1);

    // Check bit3 of flags; if set, hide icon display and clear bits 3 and 4
    if ((*(unsigned int *)(this + 0x50) >> 3 & 1) != 0) {
        callLuaFunction("HideIconDisplay", 0, gLuaState, 0);
        // Clear bits 3 and 4 (0xffffffe7 = ~0x18)
        *(unsigned int *)(this + 0x50) &= 0xffffffe7;
    }

    // +0x78: UI mode (1=something else, 2=icon wheel mode)
    if (*(int *)(this + 0x78) != 2) {
        *(int *)(this + 0x78) = 2;
        callLuaFunction("ModeChanged", 0, gLuaState, 0);
        // Set or clear bit1 of flags based on mode (though after setting to 2, this is always else)
        if (*(int *)(this + 0x78) == 1) {
            *(unsigned int *)(this + 0x50) |= 2;
        } else {
            *(unsigned int *)(this + 0x50) &= 0xfffffffd;
        }
    }

    // Update input/cursor state
    updateCursor();
    // Play sound effect (0 = stop/clear)
    playSound(0);
    // Set music or ambient state (9 = likely combat or menu)
    setMusicState(9);
}