// FUNC_NAME: Vector3::storeNormalized
void __thiscall Vector3::storeNormalized(float *out) const
{
    // Squared length of the vector (x, y, z) from this pointer.
    double sqLen = (double)(x * x + y * y + z * z);
    double factor;

    // If length is too small (within epsilon), produce a zero vector.
    if (sqLen <= (double)sEpsilon) {
        factor = 0.0;
    } else {
        // Otherwise normalize to the target length (usually 1.0).
        factor = (double)sNormalLength / sqrt(sqLen);
    }

    // Store the scaled components to the output pointer.
    out[0] = x * (float)factor;
    out[1] = y * (float)factor;
    out[2] = z * (float)factor;
}