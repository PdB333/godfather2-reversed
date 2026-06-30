// FUNC_NAME: MathUtils::lerpVector3PreserveW
// Function address: 0x006d99d0
// Performs linear interpolation between two 3D vectors (x,y,z) while preserving the w (homogeneous) component of the output vector.
// Used for smooth position transitions in the EARS engine.

void __fastcall MathUtils::lerpVector3PreserveW(float *out, float *a, float *b, float t)
{
    float w = out[3];            // preserve original w
    out[0] = t * a[0] + b[0];   // lerp x
    out[1] = t * a[1] + b[1];   // lerp y
    out[2] = t * a[2] + b[2];   // lerp z
    out[3] = w;                  // restore w
}