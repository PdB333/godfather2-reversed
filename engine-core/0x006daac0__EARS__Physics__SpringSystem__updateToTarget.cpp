// FUNC_NAME: EARS::Physics::SpringSystem::updateToTarget

void __thiscall SpringSystem::updateToTarget(float* targetPos, float deltaTime)
{
    // External globals: unknown constants
    extern float g_invMaxSteps; // _DAT_00d5f63c
    extern float g_fixedStep;   // _DAT_00d5780c

    // Compute number of substeps (clamped to 1 if negative)
    int stepCount = 1 - (int)(deltaTime * g_invMaxSteps);
    float substepTime = (g_fixedStep / (float)stepCount) * deltaTime;
    float dampingFactor = g_fixedStep - (g_fixedStep - *(float*)(this + 8)) * (g_fixedStep / (float)stepCount);

    // If stepCount <= 0, skip the loop, but we still compute the final output later
    if (stepCount > 0) {
        do {
            // Compute difference from target to current position
            float diffX = targetPos[0] - *(float*)(this + 0x10);
            float diffY = targetPos[1] - *(float*)(this + 0x14);
            float diffZ = targetPos[2] - *(float*)(this + 0x18);

            // If reflection flag is set, take absolute value of differences (for boundary wrapping)
            if (*(char*)this != 0) {
                diffX = fabs(diffX);
                diffY = fabs(diffY);
                diffZ = fabs(diffZ);
            }

            // Preserve current velocity w component
            float oldVelW = *(float*)(this + 0x2c);

            // Scale velocity by substepTime and add to current velocity
            float speedFactor = *(float*)(this + 4) * substepTime;
            *(float*)(this + 0x20) += speedFactor * diffX;
            *(float*)(this + 0x24) += speedFactor * diffY;
            *(float*)(this + 0x28) += speedFactor * diffZ;
            *(float*)(this + 0x2c) += speedFactor * 0.0f; // diffW not present, but the w component is preserved below

            // Restore original w component
            *(float*)(this + 0x2c) = oldVelW;

            // Preserve position w component
            float oldPosW = *(float*)(this + 0x1c);

            // Integrate position with velocity
            *(float*)(this + 0x10) += *(float*)(this + 0x20) * substepTime;
            *(float*)(this + 0x14) += *(float*)(this + 0x24) * substepTime;
            *(float*)(this + 0x18) += *(float*)(this + 0x28) * substepTime;
            *(float*)(this + 0x1c) += *(float*)(this + 0x2c) * substepTime;

            // Restore original w component
            *(float*)(this + 0x1c) = oldPosW;

            // Optionally apply absolute value to position (boundary reflection)
            if (*(char*)this != 0) {
                *(float*)(this + 0x10) = fabs(*(float*)(this + 0x10));
                *(float*)(this + 0x14) = fabs(*(float*)(this + 0x14));
                *(float*)(this + 0x18) = fabs(*(float*)(this + 0x18));
            }

            stepCount--;

            // Preserve current velocity w component before damping
            float velWbeforeDamping = *(float*)(this + 0x2c);

            // Damp the velocity
            *(float*)(this + 0x20) *= dampingFactor;
            *(float*)(this + 0x24) *= dampingFactor;
            *(float*)(this + 0x28) *= dampingFactor;
            *(float*)(this + 0x2c) *= dampingFactor;

            // Restore original w component
            *(float*)(this + 0x2c) = velWbeforeDamping;
        } while (stepCount != 0);
    }

    // Output the final position (w component included)
    targetPos[0] = *(float*)(this + 0x10);
    targetPos[1] = *(float*)(this + 0x14);
    targetPos[2] = *(float*)(this + 0x18);
    targetPos[3] = *(float*)(this + 0x1c);
}