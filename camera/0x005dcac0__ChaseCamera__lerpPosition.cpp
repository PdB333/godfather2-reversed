// FUNC_NAME: ChaseCamera::lerpPosition
bool __thiscall ChaseCamera::lerpPosition(float currentX, float* outX, float* outY, float blendFactor)
{
    // Checks if interpolation target is valid (e.g., camera is initialized)
    int isReady = FUN_005dc670(this);
    if (isReady != 0) {
        float currentY;   // Not explicitly initialized in decompilation; assumed set by first call to getCurrentPoint
        float targetX, targetY;

        // Fetch current camera position (overwrites currentX and sets currentY)
        FUN_005dd8a0(0, &currentX);          // Writes two floats at &currentX: currentX and currentY
        // Fetch target camera position (writes to targetX, targetY)
        FUN_005dd8a0(DAT_012056c0, &targetX); // Writes two floats at &targetX: targetX and targetY

        // interpolation factor: assume DAT_00e2b1a4 is 1.0f
        float oneMinusBlend = 1.0f - blendFactor; // DAT_00e2b1a4 is likely 1.0
        *outX = oneMinusBlend * currentX + blendFactor * targetX;
        *outY = oneMinusBlend * currentY + blendFactor * targetY;
    }
    return isReady != 0;
}