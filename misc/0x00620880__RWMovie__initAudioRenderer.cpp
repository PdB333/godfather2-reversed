// FUNC_NAME: RWMovie::initAudioRenderer
void __fastcall RWMovie::initAudioRenderer(int this) {
    char result;
    int audioParams[2]; // +0x00
    float volumeLeft; // local_10
    float volumeRight; // local_8

    RWMovie::beginInit(); // FUN_00c9eac0
    RWMovie::setAudioFormat(*(int*)(this + 8), *(int*)(*(int*)(this + 0xA0) + 0x10), 0, audioParams); // FUN_00c9cbe0

    // Convert stored int timestamps to float, handling negative sign
    volumeLeft = (float)(*(int*)(this + 0x40));
    if (*(int*)(this + 0x40) < 0) {
        volumeLeft = volumeLeft + 4294967296.0f; // DAT_00e44578
    }
    volumeRight = (float)(*(int*)(this + 0x44));
    if (*(int*)(this + 0x44) < 0) {
        volumeRight = volumeRight + 4294967296.0f; // DAT_00e44578
    }

    audioParams[0] = 0;
    RWMovie::resetAudioDevice(0, audioParams); // FUN_00c9cd40

    // Register EARS audio renderer callback for this movie
    result = RWMovie::registerAudioRenderer(this + 0xC, FUN_00620a90, this, "RWMovie AudioRenderer_EARS", 0, 0); // FUN_00ca5490
    if (result == 0) {
        *(char*)(this + 0x24) = 1; // Set error flag
    }

    RWMovie::endInit(); // FUN_00c9eae0
}