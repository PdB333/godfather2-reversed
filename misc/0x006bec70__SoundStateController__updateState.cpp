// FUNC_NAME: SoundStateController::updateState
// Function address: 0x006bec70
// Role: Updates playback state of a sound channel based on force stop flag and sound type matching.
// Uses two sound type objects at offsets +0x14 and +0x18; sound type hash 0x637b907 (likely "ambient").
// State stored at +0x40: 0=stopped, 1=idle, 2=paused, 3=playing.
// Sound handle obtained at (+0x10)->+0x38.

void __thiscall SoundStateController::updateState(int this, int forceStop)
{
    int iVar1;
    bool bVar2;

    // If not forced to stop and either sound type object matches the ambient hash
    if ((forceStop == 0) &&
        ((*(int*)(*(int*)(this + 0x14) + 0x54) == 0x637b907 ||
          (*(int*)(*(int*)(this + 0x18) + 0x54) == 0x637b907)))) {

        bVar2 = isSoundSystemMuted(); // FUN_006b34a0
        if (!bVar2) {
            // Sound system not muted
            iVar1 = *(int*)(this + 0x40);
            if (iVar1 != 1) {
                if (iVar1 == 2) {
                    // Currently paused -> stop and transition to idle
                    stopSound(*(int*)(*(int*)(this + 0x10) + 0x38)); // FUN_0093ea60
                    *(int*)(this + 0x40) = 1;
                    return;
                }
                if (iVar1 != 3) {
                    // Not playing -> start without loop and set to playing
                    startSound(*(int*)(*(int*)(this + 0x10) + 0x38), 0); // FUN_0093e960
                    *(int*)(this + 0x40) = 3;
                    return;
                }
            }
        }
        else {
            // Sound system muted
            if (*(int*)(this + 0x40) != 2) {
                // Not paused -> start with loop (paused state) and set to paused
                startSound(*(int*)(*(int*)(this + 0x10) + 0x38), 1); // FUN_0093e960
                *(int*)(this + 0x40) = 2;
                return;
            }
        }
    }
    else {
        // Force stop or sound type doesn't match
        if (*(int*)(this + 0x40) != 0) {
            // Not stopped -> stop and set to stopped
            stopSound(*(int*)(*(int*)(this + 0x10) + 0x38)); // FUN_0093ea60
            *(int*)(this + 0x40) = 0;
        }
    }
    return;
}