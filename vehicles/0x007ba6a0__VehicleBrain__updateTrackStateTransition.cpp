// FUNC_NAME: VehicleBrain::updateTrackStateTransition
void __thiscall VehicleBrain::updateTrackStateTransition(int thisPtr, int param2, int param3)
{
    // state index at this+0x188 (0x62 * 4)
    int stateIndex = *(int*)(thisPtr + 0x188);
    // flags byte at this+0x90 (0x24 * 4)
    unsigned char flags = *(unsigned char*)(thisPtr + 0x90);

    // Check if we're in a valid state and not already in track state (0x48 = 72)
    // Also ensure the "track allowed" flag (bit 4 of flags) is not set
    if (stateIndex != 0 && stateIndex != 0x48 && ((flags >> 4) & 1) == 0)
    {
        int trackIndex;
        if (stateIndex == 0)
        {
            trackIndex = 0;
        }
        else
        {
            // Convert state index to a track table index (offset by 0x48)
            trackIndex = stateIndex - 0x48;
        }

        // Check if this track index allows transition
        // (calls FUN_007b9f80 - likely a member or class-level check)
        if (isTrackStateAllowed(trackIndex) != 0)
        {
            // Retrieve the state table name string
            // thunk_FUN_004dafd0 resolves "trackToPositionAndDirectionStateTable"
            const char* stateName = getStateTableName("trackToPositionAndDirectionStateTable");

            // Call the virtual function at vtable+0x20 (likely setState or transitionTo)
            // Passing param2, param3, and the state name
            int vtable = *(int*)thisPtr;
            (*(void (__thiscall**)(int, int, const char*))(vtable + 0x20))(param2, param3, stateName);

            // Signal that we've entered the track state
            // FUN_00624ca0(1) - possibly sets a global or instance flag
            setTrackTransitionFlag(1);
        }
    }
}