// FUNC_NAME: EARSMath::computeOrientationMatrix

void EARSMath::computeOrientationMatrix(int* config, float angle, const float* inputDir, float* output)
{
    // Constants from global data
    const float kEpsilon = DAT_00e2cbe0;              // Small tolerance
    const float kOne = DAT_00e2b1a4;                   // Probably 1.0
    const float kUpRef = DAT_00e44564;                 // Reference up direction (e.g., 1.0)
    const float kYClampMin = DAT_00e44884;             // Minimum Y for clamping
    const float kYClampMax = DAT_00e44888;             // Maximum Y for clamping
    const float kMagnitudeThreshold = *(float*)PTR_FUN_00e4462c; // Threshold for zeroing direction

    float fX = inputDir[0];
    float fY = inputDir[1];
    float fZ = inputDir[2];
    float lenSq = fX*fX + fY*fY + fZ*fZ;

    float invLen;
    float len;
    if (lenSq <= kEpsilon)
    {
        invLen = 0.0f;
        len = 0.0f;
    }
    else
    {
        len = sqrtf(lenSq);
        invLen = kOne / len;
    }

    // Store normalized forward direction in output rows 1 (indices 4..6)
    output[4] = fX * invLen;
    output[5] = fY * invLen;
    output[6] = fZ * invLen;
    output[7] = 0.0f;

    // If vector length is below threshold, zero the direction, then set one component to 1.0
    // The component index is derived from config object (byte at +0x157)
    if (len < kMagnitudeThreshold)
    {
        int configVal = *config;
        output[4] = 0.0f;
        output[5] = 0.0f;
        output[6] = 0.0f;
        // Set the component indicated by config[0x157] to 1.0
        int index = *(char*)(configVal + 0x157);
        output[index + 4] = kOne;  // +4 because we start at index 4
    }

    // Now compute perpendicular vector and rotate with angle
    float vx, vy, vz;  // Temporary perpendicular vector
    float crossX, crossY, crossZ; // Cross product components for rotation basis

    // Check if Y component is outside clamped range (vertical case)
    if ((output[5] > kYClampMax) || (output[5] < kYClampMin))
    {
        float tmpZ = kUpRef - output[6];
        float len2 = output[5]*output[5] + tmpZ*tmpZ;
        float invLen2;
        if (len2 <= kEpsilon)
            invLen2 = 0.0f;
        else
            invLen2 = kOne / sqrtf(len2);

        vx = 0.0f;
        vy = invLen2 * output[5];
        vz = invLen2 * tmpZ;

        // Cross product: (output[4..6]) x (vx,vy,vz)
        crossX = output[5]*vz - output[6]*vy;
        crossY = output[6]*vx - output[4]*vz;
        crossZ = output[4]*vy - output[5]*vx;
    }
    else // Horizontal case (Y within clamp range)
    {
        float tmpZ = kUpRef - output[6];
        float vx = output[4];
        float len2 = vx*vx + tmpZ*tmpZ;
        float invLen2;
        if (len2 <= kEpsilon)
            invLen2 = 0.0f;
        else
            invLen2 = kOne / sqrtf(len2);

        vx = invLen2 * vx;
        vy = 0.0f;
        vz = invLen2 * tmpZ;

        // Cross product: (vx,vy,vz) x (output[4..6])
        crossX = vx*output[5] - vy*output[6];
        crossY = vz*output[4] - vx*output[6];
        crossZ = vy*output[4] - vz*output[5];
    }

    // Compute cos and sin of the angle
    float cosA = cosf(angle);
    float sinA = sinf(angle);

    // Compute output row 2 (indices 8..11): rotated "up" vector
    output[8]  = cosA * crossX + sinA * vx;
    output[9]  = cosA * crossY + sinA * vy;
    output[10] = cosA * crossZ + sinA * vz;
    output[11] = 0.0f;

    // Compute output row 0 (indices 0..3): rotated "right" vector
    float oneMinusCos = kUpRef - cosA;
    output[0] = oneMinusCos * vx + sinA * crossX;
    output[1] = oneMinusCos * vy + sinA * crossY;
    output[2] = oneMinusCos * vz + sinA * crossZ;
    output[3] = 0.0f;
}