// FUNC_NAME: Quaternion::normalize
// Address: 0x0055cf80
// Role: Normalize a quaternion in place. This function operates on a 4-float quaternion (x, y, z, w) as an array of floats.
void __fastcall Quaternion::normalize(float *this)
{
    float x = this[0]; // +0x0
    float y = this[1]; // +0x4
    float z = this[2]; // +0x8
    float w = this[3]; // +0xC

    float lenSq = x * x + y * y + z * z + w * w;
    if (lenSq != 0.0f)
    {
        float invLen = 1.0f / sqrtf(lenSq); // sqrtf is FUN_00414a80
        this[0] = x * invLen;
        this[1] = y * invLen;
        this[2] = z * invLen;
        this[3] = w * invLen;
    }
    // If lenSq is zero, the quaternion remains unchanged (already zero)
}