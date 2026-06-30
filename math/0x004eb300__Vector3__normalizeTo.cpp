// FUNC_NAME: Vector3::normalizeTo
void Vector3::normalizeTo(float *out) const
{
    // Load input vector components (this is the source, passed via EAX)
    float x = this->x; // +0x00
    float y = this->y; // +0x04
    float z = this->z; // +0x08

    // Compute squared length
    float lenSq = x * x + y * y + z * z;

    // Threshold constant at 0x00e2cbe0 (likely small epsilon, e.g., 0.0f or FLT_EPSILON)
    if (lenSq <= *(float*)0x00e2cbe0)
    {
        // Treat as zero vector
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
    }
    else
    {
        // Constant at 0x00e2b1a4 (likely 1.0f, used as numerator for 1/len normalization)
        float invFactor = *(float*)0x00e2b1a4 / sqrtf(lenSq);
        out[0] = x * invFactor;
        out[1] = y * invFactor;
        out[2] = z * invFactor;
    }
}