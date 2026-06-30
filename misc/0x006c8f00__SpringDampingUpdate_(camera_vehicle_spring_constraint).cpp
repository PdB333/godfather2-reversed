// FUNC_NAME: SpringDampingUpdate (camera/vehicle spring constraint)
void __thiscall SpringDampingUpdate(void* thisPtr, float springConstant, float damping, float externalForce, float timeStep, float* targetPos, float* currentPos, float* outputVelocity)
{
    float fSpringAccel;
    float fSpringForce;
    double dTmp;
    float fNewPos;
    float fDelta[3]; // {dx, dy, dz}
    float fZero[2] = {0.0f, 0.0f};

    // External flag to invert spring direction (e.g. for reverse camera)
    if (g_bInvertSpring == 0) {
        fSpringAccel = g_fZero - springConstant * externalForce * g_fOne;
    } else {
        fSpringAccel = springConstant * externalForce * g_fOne;
    }

    // Read current spring state: position and velocity
    float fCurPos = *(float*)((int)thisPtr + 0x94); // spring position offset (e.g. for camera distance)
    float fCurVel = *(float*)((int)thisPtr + 0x98); // spring velocity

    fNewPos = fCurPos - fSpringAccel; // new position after external acceleration
    float fSpringDiff = fNewPos * damping + fCurVel; // spring force (including damping)
    float fSpringFactor = (float)(g_fZero - damping * timeStep); // time integration factor

    // Update spring position with semi-implicit Euler
    fNewPos = (fSpringDiff + fNewPos) * fSpringFactor + fSpringAccel;
    *(float*)((int)thisPtr + 0x94) = fNewPos;

    // Update spring velocity (with damping)
    *(float*)((int)thisPtr + 0x98) = (fCurVel - fSpringDiff * timeStep) * fSpringFactor;

    // Compute difference between target and current position
    fDelta[0] = currentPos[0] - targetPos[0];
    fDelta[1] = currentPos[1] - targetPos[1];
    fDelta[2] = currentPos[2] - targetPos[2];

    // Apply spring displacement to the delta vector (scaled by the new spring position)
    vec3ScaleAndZero(&fDelta[0], &fDelta[0], fZero, fNewPos); // simulates FUN_004a0370

    // Move current position towards target by the scaled delta
    currentPos[0] = targetPos[0] + fDelta[0];
    currentPos[1] = targetPos[1] + fDelta[1];
    currentPos[2] = targetPos[2] + fDelta[2];

    // Compute output velocity (two components, e.g. for camera angular velocity)
    outputVelocity[0] = fDelta[1] * g_fOne; // scaled dy
    outputVelocity[1] = (g_fZero - fDelta[0]) * g_fOne; // scaled -dx
    outputVelocity[2] = 0.0f;
}