// FUNC_NAME: CameraController::updateBlendWeight
void __thiscall CameraController::updateBlendWeight(float deltaTime) {
    int playerObj = 0;
    float scalingFactor;
    float minBlend, maxBlend, blendSpeed;
    float currentTime, clampedTime, progress;

    // Check bit 1 (mask 0x4) at offset 0x2d8 (e.g., enable flag for this controller)
    if ((*(uint32_t*)(this + 0x2d8) >> 2 & 1) != 0) {
        playerObj = FUN_007079a0(); // Get player manager or current player
        if (playerObj != 0) {
            playerObj = FUN_007079a0(); // Second call – likely get player instance
            if (playerObj != 0) {
                // Check bit 1 at offset 0x8e8 (player flag, e.g., aiming?)
                if ((*(uint32_t*)(playerObj + 0x8e8) >> 2 & 1) == 0) {
                    // Check bit 23 (0x800000) at offset 0x249c (player flag, e.g., sprinting?)
                    if ((*(uint32_t*)(playerObj + 0x249c) >> 0x17 & 1) == 0) {
                        goto LAB_00702ef1;
                    }
                    scalingFactor = *(float*)(this + 0x2f4); // Sensitivity scaling for sprinting
                } else {
                    scalingFactor = *(float*)(this + 0x2f0); // Sensitivity scaling for aiming
                }
                deltaTime *= scalingFactor;
            }
        }
    }

LAB_00702ef1:
    // Get interpolation range and speed from some helper
    FUN_00702bc0(&minBlend, &maxBlend, &blendSpeed);
    blendSpeed = (maxBlend - minBlend) * blendSpeed;

    // Threshold check on speed (global)
    if (blendSpeed > DAT_00e44598) {
        currentTime = (float)FUN_00702d70(); // Get current time / progress
        // Clamp new time: currentTime + deltaTime within [minBlend, maxBlend]
        if ((float)(currentTime + deltaTime) <= maxBlend) {
            if (minBlend <= (float)(currentTime + deltaTime)) {
                clampedTime = deltaTime; // Actually deltaTime itself (but note type mismatch)
            } else {
                clampedTime = minBlend;
            }
        } else {
            clampedTime = maxBlend;
        }
        deltaTime = clampedTime; // Use clamped time as new blend value
        playerObj = (int)FUN_007079a0(); // Get player again
        if (playerObj != 0) {
            // Call virtual function at offset 0x244 with progress = (maxBlend - deltaTime) / blendSpeed
            (*(void (__thiscall**)(int, float))(*(int*)playerObj + 0x244))(playerObj, (maxBlend - deltaTime) / blendSpeed);
        }
    }
}