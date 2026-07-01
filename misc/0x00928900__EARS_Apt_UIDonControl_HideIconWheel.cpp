// Xbox PDB: EARS_Apt_UIDonControl_HideIconWheel
// FUNC_NAME: IconWheelManager::closeWheel
// Function address: 0x00928900
// This method handles the closing of the icon wheel (weapon/item selection UI).
// It clears idle flags, dispatches a hide event, and updates mode flags accordingly.

void __thiscall IconWheelManager::closeWheel(int this) // this = param_1
{
    // pointer to a structure for script call arguments
    struct ScriptArgs {
        int arg0;   // +0x00: some handle or pointer
        int arg1;   // +0x04: usually 0
        char arg2;  // +0x08: usually 0
    } args;

    // Functions (likely named based on context)
    // FUN_004252d0: probably clear some UI state or idle timer
    // FUN_009284d0: likely update current wheel state
    // FUN_005a04a0: dispatch a script event to Lua (eventName, param, paramString, paramInt)
    // FUN_005c1b40: probably resume game flow (e.g., unpause)
    // FUN_00408a00: initialize a script call with args
    // FUN_0094dc50: set some global flag (1)
    // FUN_006915e0: set game state (9)

    // Offset +0x50: flags (bit0 = idle, bit1 = mode changed)
    // Offset +0x54: reference count or active flag
    // Offset +0x78: current mode (0 = none, 1 = wheel active, etc.)

    // Clear bit0 of flags (mark as no longer idle)
    *(unsigned int*)(this + 0x50) &= 0xfffffffe;

    // Update wheel state (e.g., remove from screen)
    updateWheelState(); // FUN_009284d0

    // Send "HideIconWheel" event to script system
    dispatchScriptEvent("HideIconWheel", 0, DAT_00d87b2c, 0); // FUN_005a04a0

    // If the wheel was not already closed (active count == 0), resume game
    if (*(int*)(this + 0x54) == 0) {
        resumeGame(); // FUN_005c1b40
    }

    // Handle mode change if a previous mode was active
    if (*(int*)(this + 0x78) != 0) {
        int oldMode = *(int*)(this + 0x78);
        *(int*)(this + 0x78) = 0; // Reset mode to none
        dispatchScriptEvent("ModeChanged", 0, DAT_00d87b2c, 0); // Notify mode change

        // Update bit1 of flags based on whether the previous mode was mode 1
        if (oldMode == 1) {
            *(unsigned int*)(this + 0x50) |= 2;  // Set bit1 (mode 1 flag)
        } else {
            *(unsigned int*)(this + 0x50) &= 0xfffffffd; // Clear bit1
        }
    }

    // Build script call arguments using global handle
    args.arg0 = DAT_011302a8; // some global handle/pointer
    args.arg1 = 0;
    args.arg2 = 0;
    initScriptCall(&args, 0); // FUN_00408a00

    // Set global state flags
    setGlobalFlag(1);  // FUN_0094dc50
    setGameState(9);   // FUN_006915e0
}