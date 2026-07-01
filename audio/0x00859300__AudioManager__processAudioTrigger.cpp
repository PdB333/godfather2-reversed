// FUNC_NAME: AudioManager::processAudioTrigger

void __thiscall AudioManager::processAudioTrigger(int this, int pTrigger, int actionType)
{
    float triggerVolume = *(float *)(pTrigger + 0x2c);          // +0x2c: volume or distance threshold
    int triggerType = *(int *)(pTrigger + 0x30);               // +0x30: event type (e.g., 3 = play)

    // If action is not "stop" (3), update audio system state
    if (actionType != 3)
    {
        int audioParam = FUN_008591b0(pTrigger + 0x20);        // +0x20: sound data (e.g., ID, position)
        FUN_00858d40(triggerVolume, audioParam);                // Set volume or update source
    }

    // Check if sound system is enabled and global volume threshold allows playback
    int* soundSystem = *(int**)(this + 0xf8);                  // +0xf8: pointer to sound system (e.g., AudioDataManager)
    bool soundEnabled = (soundSystem[0x322] >> 2) & 1;         // bit 2 of soundSystem[0x322] = enable flag

    if (soundEnabled && (g_globalVolumeThreshold < triggerVolume) && (triggerType == 3))
    {
        int soundSystemInstance = (**(code **)(*soundSystem + 0x1e4))(); // vtable call to get audio controller
        if (soundSystemInstance != 0)
        {
            int soundId = FUN_00799100(0x21);                  // 0x21 = sound resource ID or event type
            int soundHandle = (**(code **)(*(int *)(soundSystemInstance + 0x1f30) + 8))(soundId); // call method at vtable+8
            FUN_00444660(soundHandle, soundId);                 // Finalize sound playback
        }
    }
}