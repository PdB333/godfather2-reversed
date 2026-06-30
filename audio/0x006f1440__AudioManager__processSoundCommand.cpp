// FUNC_NAME: AudioManager::processSoundCommand
void __thiscall AudioManager::processSoundCommand(int thisPtr, int soundId, int command)
{
    int iVar1;
    int iVar2;
    int tempCommand;
    float time;
    
    // Save command parameter (may be modified in case 2)
    tempCommand = command;
    
    // If there is a pending stream1, release/stop it
    if (*(int *)(thisPtr + 0xc) != 0) {
        FUN_006f7250(soundId, command);
    }
    
    // If there is a pending stream2, handle the command
    if (*(int *)(thisPtr + 0x10) != 0) {
        switch(tempCommand) {
        case 0: // Stop/Reset
        case 3: // Stop variant
        case 4: // Stop variant
            // Get current active stream pointer
            iVar1 = *(int *)(thisPtr + 8);
            if (iVar1 != 0) {
                iVar2 = *(int *)(iVar1 + 0x14);
                // Check if sub-stream exists and has a handle
                if ((*(int *)(iVar1 + 0xc) != 0) && (iVar2 != 0)) {
                    // Get current master time (or volume)
                    time = (float)FUN_006f4d20(DAT_01205214);
                    // Store time in active stream's volume/position field
                    *(float *)(*(int *)(thisPtr + 8) + 4) = time;
                    // Set sub-stream's state/type to original command
                    *(int *)(iVar2 + 0xc) = tempCommand;
                    // Get and play sound handle
                    tempCommand = FUN_006f52f0(); // returns some handle or flag
                    FUN_006f55b0(tempCommand);
                }
                // If flag 0x20 is set and there is a handle, release it
                if (((*(char *)(thisPtr + 0x1c) & 0x20) != 0) && (*(int *)(thisPtr + 0x14) != 0)) {
                    FUN_00815060(*(int *)(thisPtr + 0x18));
                }
                // Finalize cleanup
                FUN_006f5380();
                *(int *)(thisPtr + 8) = 0;
            }
            // Clear both pending streams
            *(int *)(thisPtr + 0x10) = 0;
            *(int *)(thisPtr + 0xc) = 0;
            break;
            
        case 1: // Check if soundId matches expected, then trigger callback
            if (soundId == *(int *)(*(int *)(thisPtr + 0x10) + 0x18)) {
                FUN_006fd930();
                return;
            }
            break;
            
        case 2: // Prepare/Load new handle
            *(int *)(thisPtr + 0x18) = 0;
            if (*(int *)(thisPtr + 0x14) != 0) {
                tempCommand = 0xffffffff; // Invalid handle sentinel
                // Query existing resource
                FUN_005e2b30(soundId, &tempCommand);
                // Create new handle from existing resource
                tempCommand = FUN_00815020(*(int *)(thisPtr + 0x14), tempCommand);
                *(int *)(thisPtr + 0x18) = tempCommand;
                return;
            }
        }
    }
    return;
}