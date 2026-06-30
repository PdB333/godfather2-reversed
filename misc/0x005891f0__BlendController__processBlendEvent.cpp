// FUNC_NAME: BlendController::processBlendEvent
char __thiscall BlendController::processBlendEvent(int this, int* blendEvent) {
    // Validate the blend event
    char result = FUN_00581f60(blendEvent);
    if (result == '\0') {
        return '\0';
    }

    // Check blend flag and internal state
    if (((char)blendEvent[4] != '\0') || (*(char *)(this + 0x30) != '\0')) {
        return result;
    }

    // Prepare local blend request structure
    int local_58 = blendEvent[0];              // +0x00: pointer to animation data
    int local_54 = this;
    undefined4 local_50 = 0xfffffffe;
    undefined4 local_4c = 0;
    char local_48 = '\0';
    undefined4 local_44 = 0;

    // Initialize blend request (FUN_00587a00 likely returns >=0 on success)
    int success = FUN_00587a00(&local_58);
    if (success < 0) {
        return '\0';
    }
    if (local_48 == '\0') {
        return '\0';
    }

    // Extract animation data pointer
    int animData = blendEvent[0];               // same as local_58 initially

    // Setup blend source/sink data (likely quaternions or blend weights)
    // From local_40 = animData, call FUN_00581d70 to fill local_30..fStack_14
    int local_40 = animData;

    undefined4 uStack_28 = 0;
    undefined4 uStack_2c = 0;
    undefined4 local_30 = 0;
    undefined4 uStack_18 = 0;
    undefined4 uStack_1c = 0;
    undefined4 local_20 = 0;

    // Retrieve blend parameters from animation data
    local_3c = *(undefined4 *)(this + 0x20);      // +0x20: some blend time/alpha
    // +0x24 in animData is a target position/offset
    local_38 = *(float *)(animData + 0x24) - DAT_00e2b1a4;  // constant likely 0.0f
    fStack_24 = DAT_00e2b1a4;
    fStack_14 = DAT_00e2b1a4;
    local_40 = animData;

    FUN_00581d70(&local_40);   // fill local_30..fStack_14 with blend info

    // Store blend target data to this object (6 consecutive floats)
    *(undefined4 *)(this + 0x40) = local_30;
    *(undefined4 *)(this + 0x44) = uStack_2c;
    *(undefined4 *)(this + 0x48) = uStack_28;
    *(float *)(this + 0x4c) = fStack_24;
    *(undefined4 *)(this + 0x50) = local_20;
    *(undefined4 *)(this + 0x54) = uStack_1c;
    *(undefined4 *)(this + 0x58) = uStack_18;
    *(float *)(this + 0x5c) = fStack_14;

    // Get current and delta time
    int currentTime = FUN_00578280();
    int deltaTime = FUN_005782a0();
    if (deltaTime == -1) {
        deltaTime = currentTime;
    }

    // Blend state fields
    float blendDuration = *(float *)(this + 0x24);    // +0x24: blend duration
    undefined4 blendTargetTime = *(undefined4 *)(this + 0x1c); // +0x1c: target blend time

    // Check if blend can start (FUN_00581b30 might verify time constraints)
    char canBlend = FUN_00581b30(animData, deltaTime);
    if (canBlend != '\0') {
        // Finalize blend: update blend start/end times
        FUN_00586a30(blendTargetTime);
        // New current blend time = event target time + blend duration
        *(float *)(this + 0x1c) = (float)blendEvent[2] + blendDuration;
        // Shift old current to previous
        *(float *)(this + 0x20) = blendDuration;
        return '\x01';
    }

    return '\0';
}