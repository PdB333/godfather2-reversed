// FUNC_NAME: computeAimPositionFromTransform
void computeAimPositionFromTransform(float *outPosition, float *outDirection, float *transform, bool useAlternateHeight, void *characterObj)
{
    float scaleX, scaleY, scaleZ;
    int result;
    float heightScale;

    // Cache heights from character object
    static int s_cachedFlags = 0;
    static float s_cachedStandHeight = 0.0f; // +0x1fac from characterObj
    static float s_cachedCrouchHeight = 0.0f; // +0x1fb4
    static float s_cachedProneHeight = 0.0f; // +0x1fb8

    if ((s_cachedFlags & 1) == 0) {
        s_cachedStandHeight = *(float *)((char *)characterObj + 0x1fac); // +0x1fac: stand height
        s_cachedFlags |= 1;
    }
    scaleY = s_cachedStandHeight;
    if ((s_cachedFlags & 2) == 0) {
        s_cachedCrouchHeight = *(float *)((char *)characterObj + 0x1fb4); // +0x1fb4: crouch height
        s_cachedFlags |= 2;
    }
    if ((s_cachedFlags & 4) == 0) {
        s_cachedProneHeight = *(float *)((char *)characterObj + 0x1fb8); // +0x1fb8: prone height
        s_cachedFlags |= 4;
    }

    // Choose height based on mode
    float chosenHeight = s_cachedCrouchHeight;
    if (useAlternateHeight) {
        chosenHeight = s_cachedProneHeight;
    }

    float flag = transform[7]; // transform[7] is flag (0.0 or denormal)
    static float someLargeConstant = *(float *)0x00e44564; // likely 1.0 or far plane

    if (flag == 0.0f) {
        // Simple offset: use stand height for all axes
        outPosition[0] = transform[3] * s_cachedStandHeight + transform[0];
        outPosition[1] = transform[4] * scaleY + transform[1];
        outPosition[2] = transform[5] * scaleY + transform[2];

        result = FUN_00471610(); // returns pointer to some object (player/ camera)
        outPosition[1] = *(float *)(result + 0x34); // override Y with something from object

        if (outDirection != NULL) {
            outDirection[0] = someLargeConstant - transform[3];
            outDirection[1] = someLargeConstant - transform[4];
            outDirection[2] = someLargeConstant - transform[5];
            return;
        }
    }
    else {
        outPosition[0] = transform[3] * chosenHeight + transform[0];
        outPosition[1] = transform[4] * chosenHeight + transform[1];
        outPosition[2] = transform[5] * chosenHeight + transform[2];

        if (flag == 1.4013e-45f) { // denormal flag indicates alternative mode (e.g., cover)
            result = FUN_00471610();
            outPosition[1] = *(float *)(result + 0x34);

            if (outDirection != NULL) {
                // Compute a cross product like direction (simplified)
                outDirection[0] = transform[5] - transform[4] * 0.0f;
                outDirection[1] = transform[3] * 0.0f - transform[5] * 0.0f;
                outDirection[2] = transform[4] * 0.0f - transform[3];
                return;
            }
        }
        else {
            result = FUN_00471610();
            outPosition[1] = *(float *)(result + 0x34);

            if (outDirection != NULL) {
                // Similar cross but then negate direction
                outDirection[0] = transform[5] - transform[4] * 0.0f;
                outDirection[1] = transform[3] * 0.0f - transform[5] * 0.0f;
                outDirection[2] = transform[4] * 0.0f - transform[3];
                outDirection[0] = someLargeConstant - outDirection[0];
                outDirection[1] = someLargeConstant - outDirection[1];
                outDirection[2] = someLargeConstant - outDirection[2];
            }
        }
    }
}