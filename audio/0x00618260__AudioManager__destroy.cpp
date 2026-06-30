// FUNC_NAME: AudioManager::destroy

void __thiscall AudioManager::destroy(int this) {
    // Call base class or common cleanup
    FUN_00612a60(); // Possibly SoundManager::stopAll()

    if (DAT_012058fc == 0 || DAT_012058fc == -1) {
        _DAT_00f1592c = 0; // Reset global state flag
    }

    // Release sound resource if present
    if (*(int*)(this + 0xA4) != 0) {
        // +0x14: handle/index, +0xA4: pointer to stream object, &DAT_00f15910: global reference, 2: release type
        FUN_0060aea0(*(undefined4*)(this + 0x14), *(int*)(this + 0xA4), &DAT_00f15910, 2); // releaseAudioStream
    }

    // Release additional resources
    if (*(int*)(this + 0xA8) != 0) {
        FUN_006063b0(); // releaseResource
    }

    if (*(int*)(this + 0xAC) != 0) {
        FUN_006063b0(); // releaseResource
    }
}