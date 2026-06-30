// FUNC_NAME: normalizeQuaternion
void __fastcall normalizeQuaternion(float* quat)
{
    float x = quat[0];
    float y = quat[1];
    float z = quat[2];
    float w = quat[3];

    float magSq = x*x + y*y + z*z + w*w;
    float invMag;

    if (magSq == 0.0f) {
        invMag = 0.0f; // zero quaternion remains zero
    } else {
        float mag = sqrtf(magSq); // FUN_00414a80 is sqrt
        invMag = 1.0f / mag;
    }

    quat[0] = x * invMag;
    quat[1] = y * invMag;
    quat[2] = z * invMag;
    quat[3] = w * invMag;
}