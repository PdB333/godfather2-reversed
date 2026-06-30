// FUNC_NAME: Vector3::normalized

void __thiscall Vector3::normalized(float *outVec) const
{
    // Input vector is 'this' (passed in ECX). Offsets: +0x00 = x, +0x04 = y, +0x08 = z.
    float x = *(float *)this;
    float y = *(float *)((int)this + 4);
    float z = *(float *)((int)this + 8);

    float sqMag = x*x + y*y + z*z;
    float scale;
    // DAT_00e2cbe0 is the epsilon threshold (likely 0.0f or very small).
    // DAT_00e2b1a4 is the target length (likely 1.0f).
    if (sqMag <= DAT_00e2cbe0)
    {
        scale = 0.0f;
    }
    else
    {
        scale = DAT_00e2b1a4 / sqrtf(sqMag);
    }

    outVec[0] = x * scale;
    outVec[1] = y * scale;
    outVec[2] = z * scale;
}