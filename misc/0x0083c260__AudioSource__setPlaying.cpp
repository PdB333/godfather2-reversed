// FUNC_NAME: AudioSource::setPlaying
// Function address: 0x0083c260
// Role: Controls playback of an audio source based on a boolean flag.
// Checks if the sound handle at +0xF4 is valid (-1 means invalid).
// If valid, calls either startSound or stopSound depending on param_3.

void __thiscall AudioSource::setPlaying(int this, undefined4 param_2, char param_3)
{
    // +0xF4: sound handle (int), -1 indicates no sound assigned
    if (*(int *)(this + 0xF4) == -1) {
        return;
    }
    if (param_3 != '\0') {
        // param_3 true: start/resume playback
        FUN_0043c490();  // likely startSound()
        return;
    }
    // param_3 false: stop playback
    FUN_0043c5b0();  // likely stopSound()
    return;
}