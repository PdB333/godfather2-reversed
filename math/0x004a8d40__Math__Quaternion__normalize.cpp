// FUNC_NAME: Math::Quaternion::normalize
// Address: 0x004a8d40
// Role: Normalize a 4-component vector (quaternion) with threshold check.
// Uses global constant DAT_00e2cbe0 (squared epsilon) and DAT_00e2b1a4 (normalization scale, usually 1.0f).
// Writes normalized result to output array.

void __thiscall Math::Quaternion::normalize(const float *thisQuat, float *outQuat)
{
    float lengthSqr = thisQuat[0] * thisQuat[0] + thisQuat[1] * thisQuat[1] 
                      + thisQuat[2] * thisQuat[2] + thisQuat[3] * thisQuat[3];
    float scale;
    // Global epsilon for avoiding division by zero (DAT_00e2cbe0)
    if (lengthSqr <= 0.0f) // DAT_00e2cbe0 might be zero or small epsilon; assume 0.0
    {
        scale = 0.0f;
    }
    else
    {
        // DAT_00e2b1a4 is the target magnitude (typically 1.0f)
        scale = 1.0f / __builtin_sqrtf(lengthSqr); // DAT_00e2b1a4 assumed 1.0
    }
    outQuat[0] = thisQuat[0] * scale;
    outQuat[1] = thisQuat[1] * scale;
    outQuat[2] = thisQuat[2] * scale;
    outQuat[3] = thisQuat[3] * scale;
}