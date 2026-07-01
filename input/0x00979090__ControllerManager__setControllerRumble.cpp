// FUNC_NAME: ControllerManager::setControllerRumble
void __thiscall ControllerManager::setControllerRumble(int thisPtr, byte rumbleFlags) {
    byte rumbleMask = 0;
    if ((rumbleFlags & 4) != 0) { // Right motor bit? (low-frequency rumble)
        rumbleMask = 1;
    }
    if ((rumbleFlags & 2) != 0) { // Left motor bit? (high-frequency rumble)
        rumbleMask = rumbleMask | 2;
    }
    if (rumbleMask != 0) {
        // Apply rumble: controller data at +0x13c, callback at 0x00976c40
        FUN_00991d10(*(undefined4 *)(thisPtr + 0x13c), rumbleMask, &LAB_00976c40);
        FUN_00976d80(1); // Enable rumble/feedback
        return;
    }
    // No rumble requested, clear
    FUN_00991cd0();
    FUN_00976d80(0); // Disable rumble/feedback
}