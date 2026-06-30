// FUNC_NAME: AudioManager::triggerEventByHash
void __thiscall AudioManager::triggerEventByHash(AudioManager* this, float* param_2)
{
    // param_2 points to a larger structure (e.g. AudioManager or SoundSystem) with a pointer at offset 0x100 to an event database
    uint32* eventDbPtr = (uint32*)((int)param_2 + 0x100); // +0x100: pointer to EventDatabase
    float* outValue = nullptr;

    // Virtual function at vtable+0x10: query event by hash (0x383225a1) and retrieve a parameter value
    bool found = (**(code**)(*(int*)*eventDbPtr + 0x10))(0x383225a1, &outValue);
    if (found && this != nullptr && *outValue != _DAT_00d577a0) {
        // If the value is not the default sentinel, process it (e.g. play sound, set parameter)
        FUN_007ac710(*outValue);
    }
}