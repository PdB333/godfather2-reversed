// FUNC_NAME: updateSteeringParameters
void updateSteeringParameters() {
    // Access thread-local storage (FS segment) to get a state byte
    // FS:[0x2c] -> pointer to TLS array, +0x34 is a specific TLS slot
    int tlsValue = *(int*)(**(int**)(/* FS segment base */ + 0x2c) + 0x34);
    int index = (tlsValue != 0) * 4; // 0 or 4

    int configIndex = *(int*)(&gSteeringConfigIndices + index); // DAT_011f6be8
    float leftVal, rightVal;

    if (configIndex == -1) {
        leftVal = 0.0f;
        rightVal = gDefaultRightVal; // DAT_00e2b1a4
    } else {
        // Index into parallel arrays of 3-float structures (vectors)
        int offset = configIndex * 3;
        leftVal = (float)(*(int*)((int)&gSteeringLeftArray + offset)); // DAT_011f6bb8
        rightVal = (float)(*(int*)((int)&gSteeringRightArray + offset)); // DAT_011f6bbc
        if (rightVal == leftVal) {
            rightVal = gDefaultEqualOverride; // DAT_00e2b19c
        }
    }

    applySteeringLimits(leftVal, rightVal); // FUN_004bd600
}