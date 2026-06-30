// FUNC_NAME: ChaseCamera::setLookAtTarget
void __thiscall ChaseCamera::setLookAtTarget(int thisPtr, int enable, float targetX, float targetY)
{
    if (enable != 0) {
        // Enable custom look-at target
        // Clear bit 1 of flags at +0xE4 to indicate "use provided target"
        *(uint *)(thisPtr + 0xe4) = *(uint *)(thisPtr + 0xe4) & 0xfffffffd;
        // Store target coordinates
        *(float *)(thisPtr + 0xb8) = targetY;  // +0xB8: look-at Y (or pitch)
        *(float *)(thisPtr + 0xb4) = targetX;  // +0xB4: look-at X (or yaw)
    } else {
        // Disable custom target, use default (0, 1)
        *(uint *)(thisPtr + 0xe4) = *(uint *)(thisPtr + 0xe4) | 2;  // Set bit 1
        *(float *)(thisPtr + 0xb8) = 1.0f;
        *(float *)(thisPtr + 0xb4) = 0.0f;
    }
}