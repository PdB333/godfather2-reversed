// FUNC_NAME: CollisionResolver::resolveContactPenetration

void __thiscall CollisionResolver::resolveContactPenetration(CollisionResolver* this, void* contactInfo, float* outputArray)
{
    float* forceAccum = outputArray + 4; // offset for force accumulation (outputArray[4..7])
    float magnitudeSqr;
    float invMagnitude;
    float timeStep;
    int iVar3;
    float localPtr; // placeholder for FUN_004af8c0 result

    // Copy contact info data (likely a quaternion or position+penetration)
    outputArray[0] = *(float*)((int)contactInfo + 0x10); // direction/vector x
    outputArray[1] = *(float*)((int)contactInfo + 0x14); // direction/vector y
    outputArray[2] = *(float*)((int)contactInfo + 0x18); // direction/vector z
    outputArray[3] = *(float*)((int)contactInfo + 0x1c); // penetration depth / w

    // Normalize the vector part (first 3 components)
    magnitudeSqr = outputArray[0] * outputArray[0] + outputArray[1] * outputArray[1] + outputArray[2] * outputArray[2];
    if (magnitudeSqr == 0.0f) {
        invMagnitude = 0.0f;
    } else {
        invMagnitude = 1.0f / sqrtf(magnitudeSqr); // sqrt via FUN_00414a80
    }
    outputArray[0] = outputArray[0] * invMagnitude;
    outputArray[1] = outputArray[1] * invMagnitude;
    outputArray[2] = outputArray[2] * invMagnitude;
    outputArray[3] = outputArray[3] * invMagnitude; // normalized depth? But overwritten below

    // Restore original depth and subtract a bias from this object
    outputArray[3] = *(float*)((int)contactInfo + 0x1c); // original depth
    outputArray[3] = outputArray[3] - *(float*)(this + 0x58); // subtract some offset (e.g., skin radius?)

    // Copy constraint/target values from this object
    outputArray[8] = *(float*)(this + 0x38); // some constraint axis
    outputArray[11] = *(float*)(this + 0x34); // another constraint value
    outputArray[9] = *(float*)(this + 0x50); // velocity x or target
    outputArray[10] = *(float*)(this + 0x54); // velocity y or target

    // Initialize force accumulator to zero
    forceAccum[0] = 0.0f;
    forceAccum[1] = 0.0f;
    forceAccum[2] = 0.0f;
    forceAccum[3] = 0.0f;
    outputArray[12] = 0.0f; // additional flag/bias

    // Process contact-specific data
    iVar3 = *(int*)((int)contactInfo + 0x28); // pointer to some structure
    if ((*(char*)(iVar3 + 0x18) == 1) && (iVar3 = *(char*)(iVar3 + 0x10) + iVar3, iVar3 != 0)) {
        // Add contact forces from contact info
        FUN_00552060(contactInfo, forceAccum);
        // Lookup additional force from resource (hash 0x2006)
        float* resourceData = (float*)FUN_004af8c0(&localPtr, 0x2006);
        if (*resourceData != 0.0f) {
            forceAccum[0] += *(float*)((int)*resourceData + 0x20);
            forceAccum[1] += *(float*)((int)*resourceData + 0x24);
            forceAccum[2] += *(float*)((int)*resourceData + 0x28);
            forceAccum[3] += *(float*)((int)*resourceData + 0x2c);
        }
        // Check pose/animation state for special handling
        if (*(char*)(iVar3 + 0xd8) == 7) {
            outputArray[12] = 2.8026e-45f; // tiny value, likely a flag
        }
        if (*(char*)(iVar3 + 0xd8) == 6) {
            outputArray[12] = 1.4013e-45f; // tiny value, likely a flag
        }
    }

    // If penetration depth is below a global threshold, apply impulse to slide object
    if (outputArray[3] < DAT_00e44778) { // global penetration threshold
        timeStep = DAT_00e44564 - outputArray[3]; // compute time correction
        if (DAT_00e39f98 < timeStep) {
            timeStep = DAT_00e39f98; // clamp time step
        }
        // Add velocity-scaled offset to force accumulator
        forceAccum[0] += *(float*)((int)contactInfo + 0x10) * timeStep;
        forceAccum[1] += *(float*)((int)contactInfo + 0x14) * timeStep;
        forceAccum[2] += *(float*)((int)contactInfo + 0x18) * timeStep;
        forceAccum[3] += *(float*)((int)contactInfo + 0x1c) * timeStep;
        outputArray[3] = 0.0f; // penetration resolved
    }
}