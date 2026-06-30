// FUNC_NAME: AudioManager::updateMusicTransition
// Reconstructed from 0x0042dde0
// Handles music crossfade/volume transitions based on game state flags and timers.
// Offsets: +0x28 = some timer, +0x38 = another timer, +0x39f8 = current music ID,
// +0x3af8 = flags (bit4 = "fade in progress"?), +0x1230 = audio output state.

int AudioManager::updateMusicTransition() {
    // Ensure global music volume targets are within bounds (0x0e = 14)
    if (gMusicVolumeTarget < 14) {
        gMusicVolumeTarget = 14;
    }
    if (14 > gMasterMusicVolumeTarget) {
        gMasterMusicVolumeTarget = 14;
    }

    gCurrentMusicState = 0; // idle

    this->stopCurrentMusic(*(int*)((char*)this + 0x39f8)); // stop music with ID

    int fadeDirection = 0; // 0x200 = fade out, 0x400 = fade in

    if (((*(uint*)((char*)this + 0x3af8) >> 4) & 1) == 0) { // bit4 not set
        if (getMusicElapsed((char*)this + 0x28, (char*)this + 0x38, 1) > 0x30) { // > 48 seconds?
            fadeDirection = 0x400; // fade in
        }
    } else {
        // bit4 is set
        if (getMusicElapsed((char*)this + 0x28, (char*)this + 0x38, 1) <= 0x30) {
            fadeDirection = 0x200; // fade out
        }
    }

    int targetVolume = gDefaultMusicVolume; // normally 100
    if (gForceMusicVolumeUp != 0 && *(int*)((char*)this + 0x39f8) != 1) {
        targetVolume = 2; // force low volume
    }

    // Start the fade transition
    fadeMusic((char*)this + 0x1230, targetVolume, 0xe1, fadeDirection); // 0xe1 = music channel?
    setMusicFadeState(0xe1, fadeDirection);

    // Finalize state
    if (gMusicVolumeTarget < 14) gMusicVolumeTarget = 14;
    if (14 > gMasterMusicVolumeTarget) gMasterMusicVolumeTarget = 14;
    gCurrentMusicState = 1; // ready

    if (gMusicVolumeTarget < 22) gMusicVolumeTarget = 22;
    gFadeActiveFlag = 1; // fade has been started
    if (22 > gMasterMusicVolumeTarget) gMasterMusicVolumeTarget = 22;

    return 1;
}