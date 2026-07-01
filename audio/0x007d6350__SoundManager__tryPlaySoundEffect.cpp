// FUNC_NAME: SoundManager::tryPlaySoundEffect
bool __fastcall SoundManager::tryPlaySoundEffect(SoundManager* this)
{
    char cIsValid;
    bool bResult;
    int iSoundHandle;
    
    if (g_fElapsedTime < *(float*)(this + 0x30)) {  // Check cooldown threshold
        int iSoundIndex = FUN_00798f50(0x35);        // Get sound resource by ID (0x35)
        cIsValid = FUN_0079e920(iSoundIndex);        // Validate sound index
        if ((cIsValid != '\0') && (cIsValid = FUN_007ab420(0x10000), cIsValid != '\0')) { // Check global flag
            iSoundHandle = FUN_007ab320();           // Obtain an audio playback handle
            FUN_0079d780(iSoundHandle);              // Play the sound through that handle
            if (iSoundHandle != 0) {
                return true;
            }
        }
    }
    return false;
}