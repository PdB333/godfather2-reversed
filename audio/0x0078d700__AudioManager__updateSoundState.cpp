// FUNC_NAME: AudioManager::updateSoundState
void __fastcall AudioManager::updateSoundState(int thisPtr)
{
    int stateIndex;
    float volume;
    int soundHandle;
    int config[2];
    char local_4;

    // Clear active timer if present (offset +0x174 likely a timer pointer or ID)
    if (*(int *)(thisPtr + 0x174) != 0) {
        config[1] = 0;
        local_4 = 0;
        config[0] = *(int *)(thisPtr + 0x174);
        clearTimer(config, 0); // FUN_00408a00 – timer kill function
    }

    // Determine current state index (0,1,2) based on global game/menu state
    if ((g_InputState != 0) && (*(int *)(g_InputState + 0xd8) != 0)) {
        // Menu/UI active – state 2
        stateIndex = 2;
    }
    else if ((g_GameState != 0) &&
             ((*(int *)(g_GameState + 100) > 7) && (*(int *)(g_GameState + 100) < 0x14))) {
        // Gameplay state (likely in-mission or free roam) – state 1
        stateIndex = 1;
    }
    else {
        // Default state (e.g., menu/pause) – state 0
        stateIndex = 0;
    }

    // Update sounds for the selected state array (offset +0x74, element size 0x24)
    if (g_SoundSystemActive != 0) {
        // First sound handle at +0x74 + stateIndex*0x24
        soundHandle = *(int *)(thisPtr + 0x74 + stateIndex * 0x24);
        if (soundHandle >= 0) {
            playSoundHandle(soundHandle); // FUN_0083b530
        }

        // Second sound handle at +0x5c + stateIndex*0x24 + 0x1c (since iVar1 = this+0x5c + state*0x24)
        soundHandle = *(int *)(thisPtr + 0x5c + stateIndex * 0x24 + 0x1c);
        if (soundHandle >= 0) {
            stopSoundHandle(soundHandle); // FUN_0083b540
        }

        // Volume for that slot (at +0x5c + state*0x24 + 0x20)
        volume = *(float *)(thisPtr + 0x5c + stateIndex * 0x24 + 0x20);
        if (volume <= g_MasterVolume) {
            resetSoundVolume(); // FUN_0083b560
        }
        else {
            setSoundVolume(volume); // FUN_0083b550
        }
    }

    // Second array at offset +0xC8 (200 decimal) with element size 0x38
    int slotBase = thisPtr + 200 + stateIndex * 0x38;

    // Update additional sound layers (music, ambience, etc.)
    if (g_MusicEnabled != 0) {
        setReverb(*(int *)(slotBase + 0x28));                // FUN_0083f3e0
        setLowPass(*(int *)(slotBase + 0x30), *(int *)(slotBase + 0x34)); // FUN_0083f3f0
        setEqualizer(*(int *)(slotBase + 0x2c));             // FUN_0083f410

        soundHandle = *(int *)(slotBase + 0x18);
        if (soundHandle >= 0) {
            playSoundHandle(soundHandle); // FUN_0083b530
        }

        soundHandle = *(int *)(slotBase + 0x1c);
        if (soundHandle >= 0) {
            stopSoundHandle(soundHandle); // FUN_0083b540
        }
    }

    if (g_AmbienceEnabled != 0) {
        setReverb(*(int *)(slotBase + 0x28));               // FUN_0083f3e0
        setLowPass(*(int *)(slotBase + 0x30), *(int *)(slotBase + 0x34)); // FUN_0083f3f0
        setEqualizer(*(int *)(slotBase + 0x2c));             // FUN_0083f410

        soundHandle = *(int *)(slotBase + 0x20);
        if (soundHandle >= 0) {
            playSoundHandle(soundHandle); // FUN_0083b530
        }

        soundHandle = *(int *)(slotBase + 0x24);
        if (soundHandle >= 0) {
            stopSoundHandle(soundHandle); // FUN_0083b540
        }
    }

    if (g_VoiceEnabled != 0) {
        setReverb(*(int *)(slotBase + 0x28));               // FUN_0083f3e0
        setLowPass(*(int *)(slotBase + 0x30), *(int *)(slotBase + 0x34)); // FUN_0083f3f0
    }

    return;
}