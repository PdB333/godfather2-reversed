// FUNC_NAME: AudioManager::setPlaybackMode
void __fastcall AudioManager::setPlaybackMode(int this_ecx, int param_edx, char param_3)
{
    // Global arrays indexed by g_audioConfigIndex (0x38 bytes per entry) and g_audioConfigIndex2 (0x3C bytes per entry)
    // DAT_01125388 -> g_audioConfigIndex
    // DAT_01125389 -> g_audioConfigIndex2
    // DAT_011252e8 -> g_audioEngine1 (pointer to some audio system)
    // DAT_011252ec -> g_audioEngine2
    // FUN_0060b020 -> AudioEngine::playSound (third arg is sound name or flag)
    // FUN_0060add0 -> AudioEngine::stopSound (third arg is sound name or flag)

    // Access first array: base = &DAT_01125408, index = g_audioConfigIndex * 0x38
    // Check if the pointer at that offset is non-zero
    if (*(int *)(&DAT_01125408 + (uint)g_audioConfigIndex * 0x38) != 0) {
        // Call playSound on engine1 with the sound instance and the second parameter (param_edx)
        FUN_0060b020(g_audioEngine1, *(int *)(&DAT_01125408 + (uint)g_audioConfigIndex * 0x38), param_edx);
    }

    // Access second element in same array? Different offset: +0x1C (since DAT_01125424 = DAT_01125408 + 0x1C)
    if (*(int *)(&DAT_01125424 + (uint)g_audioConfigIndex * 0x38) != 0) {
        char *soundSource = &DAT_011280d0; // default sound source string
        if (param_3 == '\0') {
            soundSource = &DAT_00e2e770; // alternative sound source string
        }
        // Call stopSound on engine1 with the sound instance and the selected source
        FUN_0060add0(g_audioEngine1, *(int *)(&DAT_01125424 + (uint)g_audioConfigIndex * 0x38), soundSource);
    }

    // Now handle second array: base = &DAT_011254cc, index = g_audioConfigIndex2 * 0x3C
    if (*(int *)(&DAT_011254cc + (uint)g_audioConfigIndex2 * 0x3C) != 0) {
        char *soundSource2 = &DAT_01163810; // default sound source string for engine2
        if (DAT_01163840 == '\0') {
            soundSource2 = &DAT_00e2e760; // alternative sound source string
        }
        // Call stopSound on engine2 with the sound instance and the selected source
        FUN_0060add0(g_audioEngine2, *(int *)(&DAT_011254cc + (uint)g_audioConfigIndex2 * 0x3C), soundSource2);
    }

    if (*(int *)(&DAT_011254d0 + (uint)g_audioConfigIndex2 * 0x3C) != 0) {
        char *soundSource3 = &DAT_011637d0; // default sound source string
        if (DAT_01163840 == '\0') {
            soundSource3 = &DAT_00e2e720; // alternative sound source string
        }
        // Call playSound on engine2 with the sound instance and the selected source
        FUN_0060b020(g_audioEngine2, *(int *)(&DAT_011254d0 + (uint)g_audioConfigIndex2 * 0x3C), soundSource3);
    }
}