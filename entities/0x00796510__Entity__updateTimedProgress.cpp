// FUNC_NAME: Entity::updateTimedProgress
void __thiscall Entity::updateTimedProgress(int *this, char direction, float deltaTime) {
    float randomJitterX, randomJitterY, randomJitterZ;
    float flippedDelta;
    float baseScale;
    int *randomStatePtr; // pointer to random state
    unsigned long long randomBits;
    // local_2c packed as two floats (x,z) from random source
    // local_20, local_1c, local_18 form a 3D vector (x,y,z)
    // local_24 is the y component stored separately
    // local_14 is padding

    int progressMode = this[0xb0]; // +0x2C0: mode (1=randomDirection, 2=direct, 0=from pointer)
    if (progressMode == 1) {
        // Random directional perturbation
        randomStatePtr = (int *)FUN_00471610();
        randomBits = *(unsigned long long *)randomStatePtr;
        randomJitterX = (float)(randomBits & 0xFFFFFFFF) * DAT_00d5ccf8; // lower 32 bits as float
        randomJitterZ = (float)(randomBits >> 32) * DAT_00d5ccf8;      // upper 32 bits as float
        randomJitterY = *(float *)(randomStatePtr + 1) * DAT_00d5ccf8;
    } else if (progressMode == 2) {
        // Direct random vector copy (no scaling)
        randomStatePtr = (int *)FUN_00471610();
        randomJitterX = *(float *)randomStatePtr;
        randomJitterZ = *(float *)(randomStatePtr + 1);
        randomJitterY = *(float *)(randomStatePtr + 2); // adjusted: local_24 from +1 offset? Actually local_24 from (puVar2+1) as float, so that's y
    } else {
        // Mode 0: read from another object returned by FUN_00471610
        int someObj = FUN_00471610();
        randomJitterX = *(float *)(someObj + 0x10);
        randomJitterZ = *(float *)(someObj + 0x14); // assuming 8-byte aligned, lower part
        randomJitterY = *(float *)(someObj + 0x18);
    }

    // Normalize the random vector
    float vectorX = randomJitterX;
    float vectorZ = randomJitterZ;
    float vectorY = randomJitterY;
    // call to normalize (FUN_0056afa0 probably normalizes)
    FUN_0056afa0(&vectorX, &vectorX); // note: same address for input and output; might normalize in place
    // After normalization, vectorX, vectorZ, vectorY are normalized components

    baseScale = DAT_00e44564; // some global base progress (maybe 1.0)
    float speed = (float)this[0xc4] * deltaTime; // +0x310: speed multiplier

    // Reassign vector components after normalization
    vectorX = randomJitterX; // probably re-read? Actually careful: after normalization, vectorX, vectorZ, vectorY may be different.
    vectorZ = randomJitterZ;
    vectorY = randomJitterY;

    // Apply a threshold check
    if (_DAT_00d5780c < (float)this[0xcc]) { // +0x330: some threshold
        speed = speed * DAT_00d5ddec; // adjust speed
    }

    if (direction == '\0') {
        // Decreasing progress
        float currentProgress = (float)this[0xad]; // +0x2B4: current progress value
        if (currentProgress > 0.0f) {
            float newProgress = currentProgress - speed;
            this[0xad] = (int)newProgress;
            if (newProgress <= 0.0f) {
                // Progress reached zero
                deltaTime = speed - (baseScale - newProgress); // leftover delta
                this[0xad] = 0;
                this[0xae] = 2; // +0x2B8: state = 2 (completed)
                // Check flags at bit 12 of +0x2BC
                if (((uint)this[0xaf] >> 12 & 1) != 0) {
                    FUN_006a8790(this + 0x107); // start timer/callback at +0x41C
                }
                FUN_00793800(); // some global event
                char unknownFlag = FUN_00795a90(0, 1); // returns bool
                if ((unknownFlag == '\0') && (this[0x4c] != 0)) { // +0x130: script object pointer
                    (**(code **)(*(int *)this[0x4c] + 0x44))(0x6f74af5b, 0); // call script method
                }
                baseScale = DAT_00e44564; // update base scale
            }
        }
        // Flip delta for scaling the vector
        deltaTime = baseScale - deltaTime;
        vectorX = deltaTime * vectorX;
        vectorZ = deltaTime * vectorZ;
        vectorY = deltaTime * vectorY; // y is scaled by deltaTime as well
    } else {
        // Increasing progress
        float maxProgress = (float)this[0xac]; // +0x2B0: maximum progress
        float currentProgress = (float)this[0xad] + speed;
        this[0xad] = (int)currentProgress;
        if (maxProgress <= currentProgress) {
            // Exceeded max
            this[0xa9] = this[0xab]; // +0x2A4 = +0x2AC: copy some value
            deltaTime = speed - (currentProgress - maxProgress); // leftover delta
            this[0xad] = (int)maxProgress;
            this[0xae] = 0; // state = 0 (idle? successful)
        }
        // Scale vector by deltaTime
        vectorX = vectorX * deltaTime;
        vectorZ = vectorZ * deltaTime;
        vectorY = vectorY * deltaTime;
    }

    // Build a vector from local variables (x, z, y) and call virtual function at vtable offset 100 (0x64)
    // The vector is packed as two floats (x,z) in an 8-byte followed by y as float
    // Actually the code: local_2c = CONCAT44(local_1c, local_20) then local_24 = local_18
    // So it's 3 floats: local_20 = x, local_1c = z, local_18 = y
    // Then call vtable[100] with pointer to &local_2c (which contains x,z then y immediately after)
    (**(code **)(*this + 100))(&vectorX); // Actually the code passes &local_2c, which is the start of the 3-float struct
    return;
}