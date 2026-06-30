// Address: 0x00427110
// Role: Performs a 4-component scale-and-add (out = t * a + b), then restores the 4th component of output to its original value.
// This effectively updates only the first three components (x, y, z), leaving the 4th (w) unchanged.
// Likely used for vector3 operations within a 4-element aligned structure.

// FUNC_NAME: scaleAddVector3PreserveW

void __fastcall scaleAddVector3PreserveW(float* out, float* a, float* b, float t)
{
    float originalW = out[3];

    out[0] = t * a[0] + b[0];
    out[1] = t * a[1] + b[1];
    out[2] = t * a[2] + b[2];
    out[3] = t * a[3] + b[3]; // computed but then overwritten by saved value

    out[3] = originalW; // w component preserved
}