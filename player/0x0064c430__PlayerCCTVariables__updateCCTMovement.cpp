// FUNC_NAME: PlayerCCTVariables::updateCCTMovement
void __thiscall PlayerCCTVariables::updateCCTMovement(float *targetPos, float deltaTime)
{
    float local_18;
    float local_14;
    float local_10;
    float local_c;
    float speedScale;
    float dist;
    float dx, dy, dz;
    
    local_14 = 0.0;
    local_10 = 0.0;
    local_c = 0.0;
    
    // Check if CCT is active (byte at +0x1d)
    if (*(char *)(this + 0x1d) != '\0') {
        // Calculate delta from current position (+0x20, +0x24, +0x28) to target
        local_c = targetPos[2] - *(float *)(this + 0x28);  // Z delta
        local_10 = targetPos[1] - *(float *)(this + 0x24); // Y delta
        local_14 = targetPos[0] - *(float *)(this + 0x20); // X delta
        
        // Calculate distance and apply speed scaling
        dist = SQRT(local_c * local_c + local_10 * local_10 + local_14 * local_14) *
               (DAT_00e2b1a4 / deltaTime);  // Speed multiplier
        
        // Determine speed scale based on distance thresholds
        if (dist < DAT_00e44690) {  // Close threshold
            speedScale = 0.0f;
            goto LAB_0064c503;
        }
        if (dist < DAT_00e448b4) {  // Medium threshold
            speedScale = 1.4013e-45f;  // Very small float (essentially 0)
            goto LAB_0064c503;
        }
        speedScale = 2.8026e-45f;  // Small float
        if (dist < DAT_00e448b0) goto LAB_0064c503;  // Far threshold
    }
    speedScale = 4.2039e-45f;  // Default (largest)
    
LAB_0064c503:
    local_18 = speedScale;
    FUN_0064b810(2, &local_18);  // Send speed scale as 2-byte value
    
    if (speedScale != 4.2039e-45f) {
        // Use precomputed index from lookup table
        uVar1 = (&DAT_00f0cdc4)[(int)speedScale];
        FUN_0064be30(uVar1);  // Send movement data
        FUN_0064be30(uVar1);
        FUN_0064be30(uVar1);
        return;
    }
    
    // Full position update when not moving
    local_18 = targetPos[0];
    FUN_0064b810(0x20, &local_18);  // Send X as 32-byte value
    local_18 = targetPos[1];
    FUN_0064b810(0x20, &local_18);  // Send Y as 32-byte value
    local_18 = targetPos[2];
    FUN_0064b810(0x20, &local_18);  // Send Z as 32-byte value
    return;
}