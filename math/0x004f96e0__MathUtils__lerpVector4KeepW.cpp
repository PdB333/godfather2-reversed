// FUNC_NAME: MathUtils::lerpVector4KeepW
void __fastcall MathUtils::lerpVector4KeepW(float* out, const float* a, const float* b, float t)
{
    // Interpolate x,y,z components of 4D vectors a and b by scalar t,
    // preserving the original w component of the output vector.
    // a and b are pointers to float[4], out is also float[4]
    // +0x00: x, +0x04: y, +0x08: z, +0x0C: w

    float aY = a[1];   // +0x04
    float aZ = a[2];   // +0x08
    float aW = a[3];   // +0x0C  (not used, but saved via fVar4)
    float bY = b[1];   // +0x04
    float bZ = b[2];   // +0x08
    float bW = b[3];   // +0x0C

    // Save the original w component of the output vector
    float savedW = out[3]; // +0x0C

    // Interpolate x, y, z
    out[0] = t * a[0] + b[0]; // x
    out[1] = t * aY + bY;     // y
    out[2] = t * aZ + bZ;     // z
    out[3] = t * aW + bW;     // w (but will be overwritten)

    // Restore original w
    out[3] = savedW;
}