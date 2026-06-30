// FUNC_NAME: Interpolator::evaluate
// Function at 0x0050a9d0: Interpolates between keyframes for animation/position blending.
// Parameters:
//   this (param_1) - pointer to Interpolator object
//   keyframeArray (param_2) - pointer to array of keyframe data (each 0x50 bytes)
//   outputPosition (param_3) - output float[4] (position)
// Register inputs:
//   EAX (in_EAX) - keyframe index
//   XMM5 (in_XMM5_Da) - interpolation time (t)
//   EDI (unaff_EDI) - output float[4] for second interpolated position (e.g., look-at target)
void Interpolator::evaluate(int* keyframeArray, float* outputPosition)
{
    // Constants from data section
    const float kOne = DAT_00e2b1a4;          // 1.0f
    const float kMaxSpeed = DAT_00e4492c;     // maximum interpolation speed
    const float kCoeffA = _UNK_00e2da94;      // cubic coefficient
    const float kCoeffB = _UNK_00e2da84;      // cubic coefficient
    const float kCoeffC = _UNK_00e2daa4;      // cubic coefficient
    const float kCoeffD = _UNK_00e2dab4;      // cubic coefficient
    const float kCoeffE = _DAT_00e2da90;      // quadratic coefficient
    const float kCoeffF = _DAT_00e2da80;      // quadratic coefficient
    const float kCoeffG = _DAT_00e2daa0;      // linear coefficient
    const float kCoeffH = _DAT_00e2dab0;      // constant coefficient

    // Get thread-local storage base (FS segment)
    int* tlsBase = *(int**)(*(int*)(__readfsdword(0x2c)) + 8);
    int index = in_EAX; // keyframe index from EAX

    // Access keyframe data: each keyframe is 0x50 bytes, offset 0x20 for start data
    float* keyframeStart = (float*)(index * 0x50 + *keyframeArray + 0x20 + (int)tlsBase);
    float* keyframeEnd = (float*)(index * 0x50 + *keyframeArray + 0x20 + 0x30 + (int)tlsBase); // approximate

    // Get interpolation state from this object
    float* state = *(float**)(this + 0x28); // pointer to state struct (offsets: 0x00-0x64)
    float currentTime = state[0x19]; // offset 0x64
    float speed = state[0x18];       // offset 0x60

    // Compute time difference
    float timeDiff;
    if (in_XMM5_Da >= 0.0f) {
        timeDiff = in_XMM5_Da - currentTime;
    } else {
        timeDiff = in_XMM5_Da - currentTime;
        if (timeDiff < 0.0f) timeDiff = 0.0f;
    }

    // Clamp timeDiff to 0 if negative or zero
    if (timeDiff <= 0.0f) {
        timeDiff = 0.0f;
    }

    // Apply speed scaling
    float scaledTime = speed * timeDiff;
    if (scaledTime > kMaxSpeed) {
        scaledTime = kMaxSpeed;
    }

    // Cubic interpolation factor (Hermite or similar)
    float t = scaledTime;
    float t2 = t * t;
    float t3 = t2 * t;
    float blendFactor = kCoeffE * t2 + kCoeffF * t3 + kCoeffG * t + kCoeffH * kOne;
    // Also compute derivative terms (used later)
    float derivFactor = kCoeffA * t2 + kCoeffB * t3 + kCoeffC * t + kCoeffD * kOne;

    // Get start and end positions from keyframes
    float startX = state[0];   // offset 0x00
    float startY = state[1];   // offset 0x04
    float startZ = state[2];   // offset 0x08
    float startW = state[3];   // offset 0x0C (homogeneous w)

    float endX = keyframeStart[4]; // offset 0x10 from keyframe start
    float endY = keyframeStart[5];
    float endZ = keyframeStart[6];
    float endW = keyframeStart[7];

    // Interpolate position (outputPosition)
    outputPosition[0] = blendFactor * (endX - startX) + startX;
    outputPosition[1] = blendFactor * (endY - startY) + startY;
    outputPosition[2] = blendFactor * (endZ - startZ) + startZ;
    outputPosition[3] = blendFactor * (endW - startW) + startW;

    // Compute velocity/derivative contribution
    float velocityScale = *(float*)(*(int*)(this + 0x28) + 0x6c) * derivFactor * t; // offset 0x6c
    float velX = velocityScale * (endX - startX) + keyframeStart[0];
    float velY = velocityScale * (endY - startY) + keyframeStart[1];
    float velZ = velocityScale * (endZ - startZ) + keyframeStart[2];
    float velW = velocityScale * (endW - startW) + keyframeStart[3];

    // Write second output (EDI pointer)
    unaff_EDI[0] = velX;
    unaff_EDI[1] = velY;
    unaff_EDI[2] = velZ;
    unaff_EDI[3] = velW;

    // Add linear extrapolation from state velocity
    float* stateVel = *(float**)(this + 0x28);
    unaff_EDI[0] = stateVel[0] * timeDiff + velX;
    unaff_EDI[1] = stateVel[1] * timeDiff + velY;
    unaff_EDI[2] = stateVel[2] * timeDiff + velZ;
    unaff_EDI[3] = stateVel[3] * timeDiff + velW;

    // Set homogeneous w to 1
    outputPosition[3] = kOne;
    unaff_EDI[3] = kOne;

    // If flag at +0xa8 is set, apply additional transformation (e.g., quaternion slerp)
    if (*(int*)(this + 0xa8) != 0) {
        float local[4];
        FUN_004f3aa0(outputPosition, unaff_EDI, local); // likely quaternion slerp or matrix transform
        float newX = timeDiff * local[0] + outputPosition[0];
        float newY = timeDiff * local[1] + outputPosition[1];
        float newZ = timeDiff * local[2] + outputPosition[2];
        float newW = timeDiff * local[3] + outputPosition[3];
        outputPosition[0] = newX;
        outputPosition[1] = newY;
        outputPosition[2] = newZ;
        outputPosition[3] = newW;
        unaff_EDI[0] = newX * timeDiff + unaff_EDI[0];
        unaff_EDI[1] = newY * timeDiff + unaff_EDI[1];
        unaff_EDI[2] = newZ * timeDiff + unaff_EDI[2];
        unaff_EDI[3] = newW * timeDiff + unaff_EDI[3];
    }
}