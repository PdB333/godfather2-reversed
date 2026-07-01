// FUNC_NAME: HintSoundManager::tryPlayMissionHintSound
void __fastcall HintSoundManager::tryPlayMissionHintSound(int this) {
    // Check if hint flag is set on this object (+0x1c1)
    if (*(byte *)(this + 0x1c1) != 0 &&
        // Audio manager not muted (+0x7c)
        *(byte *)(gAudioManager + 0x7c) == 0 &&
        // Game manager not paused (+0x48)
        *(byte *)(gGameManager + 0x48) == 0 &&
        // Scenario/mission manager: scenario active (+0x3c7) and not completed (+0x3c5)
        *(byte *)(gScenarioManager + 0x3c7) != 0 &&
        *(byte *)(gScenarioManager + 0x3c5) == 0) {
        // Play hint sound index 0xd
        playSoundFeedback(0xd);
    }
}