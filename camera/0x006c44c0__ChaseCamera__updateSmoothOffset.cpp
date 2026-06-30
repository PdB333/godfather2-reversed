// FUNC_NAME: ChaseCamera::updateSmoothOffset
void __thiscall ChaseCamera::updateSmoothOffset(float* outOffset, float deltaTime)
{
    // +0x214: desiredOffset (Vector3)
    // +0x220: currentOffset (Vector3)
    float* desired = (float*)(this + 0x214);
    float* current = (float*)(this + 0x220);

    // Compute distance between desired and current offsets
    float distance = (float)vectorLength(current, desired); // FUN_006c3e70 returns double
    *(float*)(this + 0x2c0) = distance; // +0x2c0: storedDistance

    // Threshold (global constant, e.g., 0.01f)
    if (globalThreshold < distance) // DAT_00e44598
    {
        // Compute intermediate offset into local buffer
        float interpolated[3];
        computeInterpolatedOffset(interpolated, current, desired, deltaTime); // FUN_006c4390

        // Get global "velocity" vector (e.g., from game time manager)
        void* globalData = getGlobalVelocitySource(); // FUN_00471610
        float speedFactor = globalSpeedMultiplier; // DAT_00d5eea0

        // Scale the global velocity by speedFactor
        float scaledVelocity[3];
        scaledVelocity[0] = *(float*)((int)globalData + 0x20) * speedFactor;
        scaledVelocity[1] = *(float*)((int)globalData + 0x24) * speedFactor;
        scaledVelocity[2] = *(float*)((int)globalData + 0x28) * speedFactor;

        // Apply smoothed offset with velocity influence
        applyOffsetWithVelocity(outOffset, interpolated, scaledVelocity, distance); // FUN_006c0b10
        return;
    }

    // If distance is small, just copy the interpolated offset directly
    computeInterpolatedOffset(outOffset, current, desired, deltaTime); // FUN_006c4390
}