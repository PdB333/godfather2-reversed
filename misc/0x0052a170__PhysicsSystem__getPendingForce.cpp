// FUNC_NAME: PhysicsSystem::getPendingForce
void __fastcall PhysicsSystem::getPendingForce(float *outVector)
{
    float maxSpeed = s_maxSpeed; // Global at 0x00e2b1a4
    float pendingDuration = s_pendingDuration; // Global at 0x01125240
    float pendingForceMagnitude = s_pendingForceMagnitude; // Global at 0x0112523c
    float pendingForceX = s_pendingForceX; // Global at 0x01125230
    float pendingForceY = s_pendingForceY; // Global at 0x01125234
    float pendingForceZ = s_pendingForceZ; // Global at 0x01125238
    float forceThreshold = s_forceThreshold; // Global at 0x00e2af44

    if (pendingDuration != 0.0f && forceThreshold <= pendingForceMagnitude)
    {
        float ratio = maxSpeed / pendingDuration;
        float scaledDuration = ratio * pendingForceMagnitude;

        float forceMagX = ratio * pendingForceX * scaledDuration;
        float forceMagY = ratio * pendingForceY * scaledDuration;
        float forceMagZ = ratio * pendingForceZ * scaledDuration;

        outVector[0] = forceMagX;
        outVector[1] = forceMagY;
        outVector[2] = forceMagZ;

        if (scaledDuration < maxSpeed)
        {
            float remaining = maxSpeed - scaledDuration;
            outVector[0] = remaining + forceMagX;
            outVector[1] = remaining + forceMagY;
            outVector[2] = remaining + forceMagZ;
        }

        // Clear pending force
        s_pendingForceX = ratio * pendingForceX * 0.0f;
        s_pendingForceY = ratio * pendingForceY * 0.0f;
        s_pendingForceZ = ratio * pendingForceZ * 0.0f;
        s_pendingForceMagnitude = scaledDuration * 0.0f;
        s_pendingDuration = 0.0f;
        return;
    }

    // Default: output constant max speed (all axes)
    outVector[0] = maxSpeed;
    outVector[1] = maxSpeed;
    outVector[2] = maxSpeed;
    outVector[3] = maxSpeed; // Potential 4th component (scale or w)
}