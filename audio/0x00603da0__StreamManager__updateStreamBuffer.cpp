// FUNC_NAME: StreamManager::updateStreamBuffer
void __thiscall StreamManager::updateStreamBuffer(int this, float volume, uint32_t param3, uint32_t param4, uint32_t param5) {
    char status;
    // Local structure for stream buffer info
    struct StreamBufferInfo {
        int buffer;
        int size;
        int flags;
        void (*callback)();
    } bufInfo;
    // Another buffer? Actually local_50[3] and local_44 seem separate
    // But from the decompile, the third argument to FUN_004d5210 is &local_60,
    // and it may fill a larger structure. We'll keep as separate locals.
    int bufferHandle; // local_60
    int bufferSize;   // local_5c
    int streamFlags;  // local_58
    void (*decodeFunc)(); // local_54 (never assigned? but likely part of struct)
    int extraBuffer[3];   // local_50
    void (*cleanupFunc)(); // local_44

    // Check if stream channels are initialized
    if (((*(uint32_t *)(this + 0x4c) >> 1) & 1) == 0) {
        initChannel(); // three times
        initChannel();
        initChannel();
        *(uint32_t *)(this + 0x4c) |= 2;
    }

    lockMutex(); // FUN_004d3fe0
    setStreamParameter(param4, &gStreamVolume, (double)volume); // FUN_004d4ad0

    // Initialize stream buffer info
    extraBuffer[0] = 0;
    extraBuffer[1] = 0;
    extraBuffer[2] = 0;
    cleanupFunc = nullptr;
    bufferHandle = 0;
    bufferSize = 0;
    streamFlags = 0;
    decodeFunc = nullptr;

    status = readStreamData(&gStreamDataPool, extraBuffer, &bufferHandle); // FUN_004d5210

    if (status == 0) {
        onStreamComplete(this, param5); // FUN_00603ec0
    } else {
        onStreamComplete(this, param5);
        unlockMutex(); // FUN_004d3e20
        copyBufferData(param3, 0x30); // FUN_004d4060
        if (bufferSize != 0) {
            prepareDecode(); // FUN_004d4300
            decodeData(bufferHandle, 0, bufferSize); // FUN_004d43f0
        }
    }

    if (bufferHandle != 0) {
        decodeFunc(); // potential null dereference if never set
    }
    if (extraBuffer[0] != 0) {
        cleanupFunc(); // potential null dereference
    }
}