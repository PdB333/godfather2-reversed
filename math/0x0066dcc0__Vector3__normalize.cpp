// FUNC_NAME: Vector3::normalize
void __thiscall Vector3::normalize(float *out) const
{
    float lengthSq = this->x * this->x + this->y * this->y + this->z * this->z;
    float invLen;

    if (lengthSq <= kZeroThresholdSq) // DAT_00e2cbe0 (e.g., 1e-6f)
    {
        invLen = 0.0f;
    }
    else
    {
        invLen = kNormalizationFactor / sqrtf(lengthSq); // DAT_00e2b1a4 (1.0f)
    }

    out[0] = this->x * invLen;
    out[1] = this->y * invLen;
    out[2] = this->z * invLen;
}