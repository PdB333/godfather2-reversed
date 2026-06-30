// FUNC_NAME: AudioManager::playSoundEvent

__thiscall void AudioManager::playSoundEvent(AudioManager *this) {
    SoundParams params; // 0x48 byte structure on stack
    const char *soundName = nullptr;
    uint32 soundHash;
    int soundType;
    int *pMessage;
    uint32 handle;

    // Release any previously active sound
    if (this->activeSoundHandle != 0) {
        SoundManager::releaseSound(this->activeSoundHandle);
        this->activeSoundHandle = 0;
    }

    // Build a hash from a global constant
    soundHash = gDefaultSoundHash; // 4-byte value at 0x0112a680

    // Determine sound type based on category and flags
    if (this->categoryFlags == 0) {
        switch (this->soundType) {
        case 0:
        case 2:
            soundType = 0xB; // ambient
            goto getSoundName;
        default:
            // For cases not listed, skip further processing
            break;
        case 3:
            soundType = 10; // impact?
            break;
        case 4:
            soundType = 1; // dialog?
            break;
        case 5:
            soundType = 0x2F; // car?
            break;
        case 7:
            soundType = 0x2D; // explosion?
            break;
        case 8:
            soundType = 0; // UI?
            break;
        }
    } else {
        soundType = 0xB;
getSoundName:
        // Get the sound name from the audio data manager using the bank hash
        uint32 bankHash = this->audioDataHash;
        soundName = AudioDataManager::getSoundName(bankHash);
        if (soundName == nullptr) {
            soundName = gDefaultSoundName; // at 0x0120546e
        }
    }

    // Initialize parameter array (first 3 elements zero, then some defaults)
    params.field_0 = 0;
    params.field_4 = 0;
    params.field_8 = 0;

    // Prepare message (if any)
    pMessage = (int *)AudioManager::getMessageQueue(this->messageQueue);
    if (pMessage != nullptr) {
        *pMessage = this->messageQueue; // store pointer back? (likely a linked list operation)
    }

    // Fill sound parameters struct with globals and position
    params.field_C = gDefaultFloat; // e.g., 1.0f
    params.field_10 = 0;
    params.field_14 = 0;
    params.field_18 = 0;
    params.field_1C = gDefaultFloat;
    params.field_20 = 0;
    params.field_24 = 0;
    params.field_28 = 0;
    params.field_2C = 0;
    params.field_30 = gDefaultFloat;
    params.field_34 = 0;
    params.position.x = this->positionX; // +0x10
    params.position.y = this->positionY; // +0x14
    params.position.z = this->positionZ; // +0x18
    params.field_44 = gDefaultFloat;

    // Create the sound object
    handle = SoundEngine::createSound(soundType, &params.field_C, 0, 3, 0, 0, 1, &params, 0, 0, 0, soundName);
    this->activeSoundHandle = handle;

    // If a buffer was allocated, release it
    if (params.field_0 != 0) {
        Memory::freeBuffer(params.field_0);
    }

    // If handle is valid, set additional parameters
    if (this->activeSoundHandle != 0) {
        SoundEngine::fillSoundParameters(&soundHash, this->audioDataHash);
        SoundEngine::applySoundParameters(this->activeSoundHandle, soundHash, 
                                          (uint32)((uint16)((soundHash >> 16) | (soundHash >> 8))),
                                          (uint32)((uint8)(soundHash >> 24) | (soundHash >> 16)));
    }
}