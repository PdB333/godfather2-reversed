//FUNC_NAME: SimObject::releaseResources
void SimObject::releaseResources() {
    uint* handlePtr;

    // Release first handle (offset +0x34)
    handlePtr = *(uint**)(this + 0x34);
    if (handlePtr != nullptr) {
        // Call release function from global table indexed by handle ID
        (*(code**)(&gReleaseTable + (*handlePtr & 0x7fff) * 4))(handlePtr);
    }
    *(undefined4*)(this + 0x34) = 0;

    // Free allocated memory (offset +0x50)
    if (*(int*)(this + 0x50) != 0) {
        (*gFreeFunc)(*(int*)(this + 0x50), 0x30);
        *(undefined4*)(this + 0x50) = 0;
    }

    // Release second handle (offset +0x54)
    handlePtr = *(uint**)(this + 0x54);
    if (handlePtr != nullptr) {
        (*(code**)(&gReleaseTable + (*handlePtr & 0x7fff) * 4))(handlePtr);
    }
    *(undefined4*)(this + 0x54) = 0;

    // Call additional cleanup functions
    FUN_005aa3d0(); // releaseSubsystemA
    FUN_005b2380(); // releaseSubsystemB

    // Clear pointer at offset +0x58
    *(undefined4*)(this + 0x58) = 0;
}