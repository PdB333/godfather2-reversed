// FUNC_NAME: Math::axisAngleToQuaternion
// Address: 0x0056d1f0
// Converts an axis-angle rotation (stored as a 3D vector where magnitude = angle in radians)
// to a quaternion (x, y, z, w).
// Note: param_1[0..2] = axis * angle; param_1[3] is unused.
// param_2[0..3] = output quaternion (x, y, z, w).

void axisAngleToQuaternion(const float* inAxisAngle, float* outQuat)
{
    // Constants from data section (inferred from context)
    const float epsilon = *reinterpret_cast<const float*>(0x00e2e210); // ~0.0f
    const float halfFactor = *reinterpret_cast<const float*>(0x00e2cd54); // likely 0.5f
    const float one = *reinterpret_cast<const float*>(0x00e2b1a4); // likely 1.0f

    // Compute length of axis-angle vector (this is the rotation angle in radians)
    float length = sqrtf(inAxisAngle[0] * inAxisAngle[0] +
                         inAxisAngle[1] * inAxisAngle[1] +
                         inAxisAngle[2] * inAxisAngle[2]);

    if (length < epsilon) {
        // Zero rotation -> identity quaternion
        outQuat[0] = 0.0f;
        outQuat[1] = 0.0f;
        outQuat[2] = 0.0f;
        outQuat[3] = one; // w = 1
        return;
    }

    // Half-angle
    double halfAngleDouble = static_cast<double>(length * halfFactor);
    // The call to FUN_00b99e20 seems to be a sincos function that modifies FPU state,
    // but decompiler failed to capture its output. We assume it computes sin(halfAngle) and
    // cos(halfAngle) and stores them. For reconstruction, we directly compute them.
    // (Actual assembly likely uses fsincos after loading halfAngleDouble.)
    float halfAngle = static_cast<float>(halfAngleDouble);
    float sinHalf = sinf(halfAngle);
    float cosHalf = cosf(halfAngle);

    // Compute scale factor: sin(angle/2) / angle
    float scale = sinHalf / length;

    // Set quaternion components
    outQuat[0] = scale * inAxisAngle[0];
    outQuat[1] = scale * inAxisAngle[1];
    outQuat[2] = scale * inAxisAngle[2];
    outQuat[3] = cosHalf;

    // Note: The original decompiled code has a confusing re-assignment of w to halfAngle
    // and uses sqrt(1 - halfAngle^2) which is an approximation; this reconstruction uses
    // the correct trigonometric functions.
}