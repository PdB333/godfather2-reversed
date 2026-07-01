// FUNC_NAME: SoundSource::updateSound
void __thiscall SoundSource::updateSound(int this, char forcePlay)
{
    char isPlaying;
    undefined4 *soundDataPtr;
    int soundHandle;
    undefined4 uVar4;
    // Sound parameters structure (64 bytes)
    undefined4 soundParams[16]; // local_90 to local_54
    // Temporary buffer for updating sound (76 bytes)
    char tempBuffer[76]; // local_50

    // Get sound data pointer from global manager
    if (*(int *)(DAT_0112aa1c + 0x2c88) == 0) {
        soundDataPtr = (undefined4 *)0x0;
    } else {
        soundDataPtr = (undefined4 *)FUN_007857b0(this); // getSoundData
    }

    soundHandle = *(int *)(this + 0x30); // current sound handle
    if ((soundHandle != -1) &&
        ((forcePlay == '\0' ||
          ((soundDataPtr != (undefined4 *)0x0 && (isPlaying = FUN_00461f90(this + 0x44), isPlaying != '\0')))))) {
        // If sound is already playing and we are not forcing, or if forcePlay but sound is valid and playing?
        // Actually condition: if handle != -1 AND (forcePlay==0 OR (dataPtr!=0 AND check(this+0x44) !=0))
        // If true, stop the sound
        if (DAT_0112af90 != 0) {
            FUN_009450b0(soundHandle); // stopSoundByHandle
        }
        *(undefined4 *)(this + 0x30) = 0xffffffff; // invalidate handle
    }

    if (forcePlay != '\0') {
        if (soundDataPtr != (undefined4 *)0x0) {
            // Build sound parameters from member data and globals
            soundParams[14] = *(undefined4 *)(this + 0x18); // local_58
            soundParams[15] = _DAT_00d5780c; // local_54
            soundParams[3] = 0; // local_84
            soundParams[4] = 0; // local_80
            soundParams[2] = 0; // local_88
            soundParams[1] = 0; // local_8c
            soundParams[7] = 0; // local_74
            soundParams[9] = 0; // local_6c
            soundParams[8] = 0; // local_70
            soundParams[6] = 0; // local_78
            soundParams[11] = 0; // local_64
            soundParams[0] = DAT_00e527a4; // local_90
            soundParams[5] = DAT_00e527a4; // local_7c
            soundParams[10] = DAT_00e527a4; // local_68
            soundParams[12] = *(undefined4 *)(this + 0x10); // local_60
            soundParams[13] = DAT_00e527a0 + *(float *)(this + 0x14); // local_5c

            // Override pitch/volume from global if available
            if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
                int iVar3 = FUN_00471610(); // getAudioSettings
                soundParams[13] = *(float *)(iVar3 + 0x34); // override pitch
            }

            if ((*(int *)(this + 0x30) == -1) ||
                (isPlaying = FUN_00943c00(*(int *)(this + 0x30)), isPlaying == '\0')) {
                // Sound not playing or handle invalid: play new sound
                uVar4 = FUN_00944f40(soundDataPtr, &soundParams); // playSound
                *(undefined4 *)(this + 0x30) = uVar4;
                // Copy sound data from pointer to this object
                *(undefined4 *)(this + 0x44) = *soundDataPtr;
                *(undefined4 *)(this + 0x48) = soundDataPtr[1];
                *(undefined4 *)(this + 0x4c) = soundDataPtr[2];
                *(undefined4 *)(this + 0x50) = soundDataPtr[3];
            } else {
                // Sound already playing: update it
                FUN_0044b4e0(tempBuffer, &soundParams); // memcpy to temp
                FUN_00943ac0(*(undefined4 *)(this + 0x30)); // stopSound
                FUN_004df720(tempBuffer); // free temp? Actually might be update
            }
            // Set a parameter on the sound (e.g., volume or pitch)
            FUN_00943b00(*(undefined4 *)(this + 0x30), *(undefined4 *)(this + 0x1c));
            return;
        }
        return;
    }
    return;
}