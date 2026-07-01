// FUNC_NAME: AudioManager::getAudioParameter
// Function address: 0x0079eb40
// Role: Checks an audio flag, then retrieves a float parameter if enabled.
// This is a member function of a large class (likely AudioManager or similar).
// Offset 0x249c is a bitfield flag; bit 1 (0x2) indicates audio parameter retrieval is allowed.
// Callees: FUN_00481620 (likely isAudioEnabled), FUN_00465ca0 (likely getFloatParameter).

float AudioManager::getAudioParameter(int param2, int param3)
{
    // Check bit 1 of the audio flag at offset 0x249c
    if ((*(uint32_t*)(this + 0x249c) >> 1) & 1) {
        // Check if audio is active (e.g., not muted or disabled)
        if (isAudioEnabled()) {
            // Retrieve the actual float parameter value
            return getFloatParameter(param2, param3);
        }
    }
    return 0.0f;
}