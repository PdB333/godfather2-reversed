// FUNC_NAME: PlayerGroundSM::handleFootstepEvent
void __thiscall PlayerGroundSM::handleFootstepEvent(int previousState, int currentState)
{
    // +0x130: pointer to audio component or sound manager object
    // +0x290: bitfield (bit 29 indicates footstep sound active)
    // +0x3c: world position (likely Float3 X component)
    // DAT_0112a648: global audio data manager (e.g., gAudioDataManager)
    // DAT_00e44590: global footstep volume scale factor (e.g., gFootstepVolumeScale)
    // _DAT_00d5ca64: base footstep volume (e.g., gFootstepVolumeBase)

    int *audioComponent = *(int **)(this + 0x130);
    if (audioComponent == (int *)0x0) {
        return;
    }

    // Transition to state 4 (e.g., running) from non-4 state (e.g., walking)
    if ((currentState == 4) && (previousState != 4)) {
        // Check if footstep sound is not already playing
        if ((*(uint *)(this + 0x290) >> 0x1d & 1) == 0) {
            // Set flag: footstep sound active
            *(uint *)(this + 0x290) = *(uint *)(this + 0x290) | 0x20000000;

            // Play randomized footstep sound at position
            int random = _rand();
            float volume = (float)random * DAT_00e44590 * _DAT_00d5ca64;
            FUN_00440590(&DAT_0112a648, this + 0x3c, volume, 0, 0);
        }
    }
    else {
        // For other state transitions (or staying in same state), stop footstep sound
        // Call virtual method at offset 0x44 on audio component (likely stopSound)
        (**(code **)(*audioComponent + 0x44))(0xf86f4484, currentState);
        // Clear flag: footstep sound inactive
        *(uint *)(this + 0x290) = *(uint *)(this + 0x290) & 0xdfffffff;
    }
}