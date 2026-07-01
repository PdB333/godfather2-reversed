// FUNC_NAME: normalizeQuaternion (or normalizeVector4)
// Address: 0x00994810
// Normalizes a 4-component vector (likely a quaternion) to the length stored in the global constant _DAT_00d5780c.
// If the vector length is zero, it remains zero.

void __fastcall normalizeQuaternion(float* quat)
{
    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    float lenSq = x * x + y * y + z * z + w * w;
    float scale;
    if (lenSq == 0.0f)
    {
        scale = 0.0f;
    }
    else
    {
        // _DAT_00d5780c is a global constant (likely 1.0f for unit length)
        scale = _DAT_00d5780c / sqrtf(lenSq);
    }

    quat[0] = x * scale;
    quat[1] = y * scale;
    quat[2] = z * scale;
    quat[3] = w * scale;
}