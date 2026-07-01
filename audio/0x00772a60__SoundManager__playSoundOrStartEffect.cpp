// FUNC_NAME: SoundManager::playSoundOrStartEffect
// Reconstructed C++ function for address 0x00772a60
// Role: Plays a sound effect or starts an audio event. 
//   Handles both ID-less (ambient?) and ID-based sounds. 
//   Stores the resulting sound handle in the audio system state.

void __thiscall SoundManager::playSound(int* thisPtr, int soundId, char param_3)
{
    int* audioSystem = *(int**)(thisPtr[0x28]);  // this + 0xA0 -> audio system pointer
    int* iVar2; // pointer to some state within audio system
    int soundHandle;
    char cVar3;
    
    iVar2 = *(int**)((int)audioSystem + 0x2124); // audioSystem + 0x2124 -> some state pointer
    if (iVar2 != 0) {
        thisPtr[0x29] = 0; // reset sound handle (this + 0xA4)
        if (soundId == 0) {
            if ((param_3 == '\0') && (cVar3 = isSoundEnabled(), cVar3 != '\0')) {
                soundHandle = allocateSoundChannel(1);
                thisPtr[0x29] = soundHandle;
                cVar3 = (*(code **)(*thisPtr + 0x2c))(soundHandle, 1, 1, 0, 1.0f, 1.0f);
                if (cVar3 != '\0') {
                    iVar2[0x24] = soundHandle; // store handle in audio state
                    iVar2[0x20] |= 0x200; // set flag indicating active sound
                }
            }
        }
        else if (param_3 == '\0') {
            loadSoundById(soundId, &soundHandle);
            cVar3 = (*(code **)(*thisPtr + 0x2c))(soundHandle, 1, 1, 0, 1.0f, 1.0f);
            if (cVar3 != '\0') {
                iVar2[0x24] = soundHandle;
                iVar2[0x20] |= 0x200;
                return;
            }
        }
    }
    return;
}