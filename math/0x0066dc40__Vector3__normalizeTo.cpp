// FUNC_NAME: Vector3::normalizeTo
void __fastcall Vector3::normalizeTo(Vector3 *out) const
{
    // Constants from data section (likely set to 1e-10 and 1.0f)
    static const float kEpsilon = *(float*)0x00e2cbe0;
    static const float kScale = *(float*)0x00e2b1a4;

    float x = this->x;       // +0x00
    float y = this->y;       // +0x04
    float z = this->z;       // +0x08
    float lenSqr = x*x + y*y + z*z;

    if (lenSqr <= kEpsilon) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
    } else {
        float invLen = kScale / sqrt(lenSqr);
        out->x = x * invLen;
        out->y = y * invLen;
        out->z = z * invLen;
    }
}