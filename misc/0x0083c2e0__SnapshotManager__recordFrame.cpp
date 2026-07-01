// FUNC_NAME: SnapshotManager::recordFrame

char __thiscall SnapshotManager::recordFrame(SnapshotManager *this, undefined4 param_2)
{
    void **objectIter;
    char result;
    uint maxSnapshots;
    int *objectArray;
    int offset;
    int *snapshotData;
    char local_dummy;
    int *snapshotOut; // iStack_10, iStack_c, iStack_8, iStack_4 combined as quat
    int quatX, quatY, quatZ, quatW;
    int timestamp;
    bool needsSnapshot;

    offset = gGameState->someFlags; // DAT_01129948 + 0x4c bit5 check later
    timestamp = 0xffffffff;
    result = false;

    if (gIsRecordingEnabled) { // DAT_00e53f38
        bool paused = isPaused(); // FUN_00842870
        if (!paused && ((*(uint *)(offset + 0x4c) >> 5 & 1) == 0)) {
            bool recording = isRecording(); // FUN_008fc7b0
            if (!recording) {
                bool shouldRecord = this->vtable->shouldRecord(); // vtable[0x24]
                if (shouldRecord) {
                    int snapshotCount = this->snapshotCount; // +0x24
                    int someOffset = this->maxSnapshotOffset; // +0x26
                    maxSnapshots = getMaxSnapshots(); // FUN_0083c160
                    needsSnapshot = (snapshotCount + someOffset) < maxSnapshots;

                    // Iterate over recordable objects array
                    objectArray = &this->recordableObjects[0].ptr; // +0x40
                    snapshotOut = nullptr;
                    int snapIdx[4] = {0,0,0,0};
                    for (objectIter = (void**)objectArray; objectIter != objectArray + this->recordableObjectCount * 2; objectIter += 2) {
                        void *objectVtable = *objectIter;
                        char iterResult = objectVtable->checkTakeSnapshot( this->someId, // +0x3e
                                                                           this,
                                                                           needsSnapshot,
                                                                           &snapshotOut,
                                                                           &snapIdx,
                                                                           &timestamp);
                        if (iterResult) break;
                    }

                    bool isServer = ::isServer(); // FUN_004209a0
                    if (isServer && (char)needsSnapshot) {
                        snapshotOut = this;
                        int *quatData = (int*)this->vtable->getReadQuaternion(param_2); // vtable[0x1c]
                        if (quatData) {
                            bool valid = copyQuaternion(quatData); // FUN_00445250
                            if (valid) {
                                snapIdx[0] = quatData[0];
                                snapIdx[1] = quatData[1];
                                snapIdx[2] = quatData[2];
                                snapIdx[3] = quatData[3];
                            }
                        }
                    }

                    bool isServer2 = ::isServer(); // FUN_004209a0 again
                    if (!isServer2) {
                        if (isNonZeroQuaternion(&snapIdx)) { // FUN_008eadd0
                            this->snapshotCount++;
                            this->storedQuat.x = snapIdx[0];
                            this->storedQuat.y = snapIdx[1];
                            this->storedQuat.z = snapIdx[2];
                            this->storedQuat.w = snapIdx[3];

                            result = storeSnapshot(&snapIdx, timestamp, snapshotOut, 0); // FUN_008f0bb0
                            if (!result) {
                                this->storedQuat.w = 0;
                                this->storedQuat.z = 0;
                                this->storedQuat.y = 0;
                                this->storedQuat.x = 0;
                                this->snapshotCount--;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}