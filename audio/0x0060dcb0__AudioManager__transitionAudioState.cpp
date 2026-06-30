// FUNC_NAME: AudioManager::transitionAudioState
/*
 * Function at 0x0060dcb0: AudioManager::transitionAudioState
 * Manages a two-phase state transition for audio system: saves current state globals,
 * sets new state, triggers a scoped change (likely for bank loading or DSP effect),
 * then flushes and restores, and also sets volume parameters.
 * The param_ecx (__fastcall first arg) is passed to the inner state functions,
 * possibly indicating a bank or channel index.
 */
void __fastcall AudioManager::transitionAudioState(uint32_t param_ecx)
{
    uint32_t uVar1, uVar2;

    // Save current audio state A (low/high parts)
    uVar2 = g_audioStateA_high;   // DAT_011f3914
    uVar1 = g_audioStateA_low;    // DAT_011f3910

    // Set new state A from global template
    g_audioStateA_low = g_newAudioStateA_low;   // DAT_012058a8
    g_audioStateA_high = 0;                      // DAT_011f3914 = 0

    // Notify state change with type 4, passing old state and the ecx parameter
    AudioManager::setAudioState(4, uVar1, uVar2, param_ecx);

    // Flush / update audio processing
    AudioManager::flushAudio();   // FUN_0060dc10

    // Save again (post-flush)
    uVar2 = g_audioStateA_high;
    uVar1 = g_audioStateA_low;

    // Set the same new state again
    g_audioStateA_low = g_newAudioStateA_low;
    g_audioStateA_high = 0;

    // Second call with only old state (no ecx param)
    AudioManager::setAudioState(4, uVar1, uVar2);

    // Now handle audio state B (different pair)
    uVar2 = g_audioStateB_high;   // DAT_011f38f4
    uVar1 = g_audioStateB_low;    // DAT_011f38f0

    g_audioStateB_low = g_newAudioStateB_low;   // DAT_012058a4
    g_audioStateB_high = 0;

    // Notify state change with type 0
    AudioManager::setAudioState(0, uVar1, uVar2);

    // Set audio volume / spatial parameters (all zeros and 1.0 floats)
    AudioManager::setAudioVolume(0.0f, 0.0f, 0.0f, 1.0f, 1.0f);   // FUN_0060db60
}