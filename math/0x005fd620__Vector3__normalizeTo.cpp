// FUNC_NAME: Vector3::normalizeTo
void Vector3::normalizeTo(float *out) const
{
    // Compute squared length
    float lengthSq = x * x + y * y + z * z;

    // Check against epsilon to avoid division by zero
    if (lengthSq <= kEpsilon) {
        lengthSq = 0.0f;
    } else {
        lengthSq = kOneOverSqrtConstant / sqrtf(lengthSq); // DAT_00e2b1a4 likely 1.0f
    }

    out[0] = x * lengthSq;
    out[1] = y * lengthSq;
    out[2] = z * lengthSq;
}