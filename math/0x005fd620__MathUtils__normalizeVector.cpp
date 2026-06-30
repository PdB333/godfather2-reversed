// FUNC_NAME: MathUtils::normalizeVector
void __fastcall MathUtils::normalizeVector(Vector3* out, const Vector3* in)
{
    // out and in are 3D vectors.
    // DAT_00e2cbe0 = epsilon threshold (likely 0.0f)
    // DAT_00e2b1a4 = scaling constant (likely 1.0f)
    float sqLen = in->x * in->x + in->y * in->y + in->z * in->z;
    if (sqLen <= c_fEpsilon) // c_fEpsilon == DAT_00e2cbe0
    {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
    }
    else
    {
        float invScale = c_fUnitScale / sqrt(sqLen); // c_fUnitScale == DAT_00e2b1a4
        out->x = in->x * invScale;
        out->y = in->y * invScale;
        out->z = in->z * invScale;
    }
}