// FUNC_NAME: MultiTrackStream::processCommand
void __thiscall MultiTrackStream::processCommand(int thisPtr, int *cmdPtr)
{
    int state;
    int trackResult;
    int localObj;

    state = thisPtr; // local_4 = param_1
    // Compare command ID with stored track IDs
    if (*cmdPtr == *(int *)(thisPtr + 0x14)) {
        // Command matches track A ID
        // Check if any of the four track slots are active (non-zero)
        // Also check that state (offset 0x34) is either 0 (idle) or 0x48 (playing)
        if (((((*(int *)(thisPtr + 0x24) != 0) || (*(int *)(thisPtr + 0x28) != 0)) ||
             (*(int *)(thisPtr + 0x2c) != 0)) || (*(int *)(thisPtr + 0x30) != 0)) &&
            ((*(int *)(thisPtr + 0x34) == 0 || (*(int *)(thisPtr + 0x34) == 0x48)))) {
            // Prepare command pointer with lower byte masked (likely for alignment/slot index)
            cmdPtr = (int *)((uint)cmdPtr & 0xffffff00);
            // Find or allocate a track buffer using the masked pointer
            trackResult = FUN_00448100(thisPtr + 0x24, &cmdPtr);
            if (trackResult != 0) {
                state = 0;
                // Look up an object by hash (0x2e5f1298) in the track buffer
                // The hash might represent a "stop" or "pause" command
                if (FUN_006a4e80(trackResult, 0x2e5f1298, &state) != '\0') {
                    // Process the found object
                    FUN_006a4e40(state);
                }
            }
        }
        // Now handle the state at offset 0x34
        cmdPtr = (int *)(thisPtr + 0x34);
        if ((*(int *)(thisPtr + 0x34) != 0) && (*(int *)(thisPtr + 0x34) != 0x48)) {
            // Unexpected state → stop playback
            FUN_006a55a0();
            return;
        }
    }
    else if (*cmdPtr == *(int *)(thisPtr + 0x1c)) {
        // Command matches track B ID
        cmdPtr = (int *)(thisPtr + 0x34);
        if ((*(int *)(thisPtr + 0x34) != 0) && (*(int *)(thisPtr + 0x34) != 0x48)) {
            // Unexpected state → pause/stop playback
            FUN_006a55f0();
            return;
        }
    }
    return;
}