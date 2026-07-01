// FUNC_NAME: Player::playSoundImpact
void __fastcall Player::playSoundImpact(int *thisPtr)
{
    char isActive;
    int somePtr;
    float scaledVolume;
    // Stack structure for sound parameters
    struct SoundParams { // offset comments approximate
        undefined4 pad_00[4]; // auStack_48
        int smartPtr1;        // iStack_44
        undefined4 field_08;  // uStack_40
        int smartPtr2[2];     // aiStack_3c
        double posX;          // uStack_34 (maybe two floats)
        undefined4 posY;      // uStack_2c
        double dirX;          // uStack_28 (maybe facing direction)
        undefined4 dirY;      // uStack_20
        float volume;         // fStack_1c
        int category;         // uStack_18 = 9
        int priority;         // uStack_10 = 2
        int unk1;             // uStack_c = 0
        int masterVolume;     // uStack_8 = gMasterVolume
    } params;

    // Check if sound playback is allowed (bit 22 at offset 0x8E8)
    if (((uint)thisPtr[0x23a] >> 0x16 & 1) != 0) {
        // Virtual call at vtable+0x78 (e.g., isSoundEnabled)
        isActive = (**(code **)(*thisPtr + 0x78))();
        if (isActive) {
            // Scale volume from component value and global multiplier
            scaledVolume = (float)thisPtr[0x74c] * gVolumeMultiplier; // offset 0x1D30

            // Setup context (maybe clear or reset)
            FUN_0084dd20();

            // Release previous smart pointers if any
            if (params.smartPtr2[0] != 0) {
                releaseSmartPtr(params.smartPtr2);
                params.smartPtr2[0] = 0;
            }

            // Assignment for another smart pointer
            int newPtr = params.smartPtr2[0];
            if (params.smartPtr1 != newPtr) {
                if (params.smartPtr1 != 0) {
                    releaseSmartPtr(&params.smartPtr1);
                }
                params.smartPtr1 = newPtr;
                if (newPtr != 0) {
                    params.field_08 = *(undefined4 *)(newPtr + 4);
                    *(int **)(newPtr + 4) = &params.smartPtr1;
                }
            }

            // Get player/camera position and orientation
            somePtr = getPlayerOrCamera(); // returns pointer to e.g., Player or Camera
            params.posX = *(double *)(somePtr + 0x30);
            params.posY = *(undefined4 *)(somePtr + 0x38);

            somePtr = getPlayerOrCamera(); // again (should be same)
            params.dirX = *(double *)(somePtr + 0x30);
            params.dirY = *(undefined4 *)(somePtr + 0x38);

            // Set sound parameters
            params.category = 9;      // e.g., SFX
            params.priority = 2;      // e.g., high
            params.unk1 = 0;
            params.masterVolume = gMasterVolume; // global
            params.volume = scaledVolume;

            // Play the sound at the given location
            playSound(&gSoundEventName, thisPtr + 0xf, ¶ms, 0);

            // Clean up smart pointers
            if (params.smartPtr2[0] != 0) {
                releaseSmartPtr(params.smartPtr2);
            }
            if (params.smartPtr1 != 0) {
                releaseSmartPtr(&params.smartPtr1);
            }
        }
    }
}