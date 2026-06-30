// FUNC_NAME: math_subVec3PreserveW
void __fastcall subVec3PreserveW(float* out, const float* a, const float* b)
{
    // Save the original 4th component (preserved after subtraction)
    float origW = out[3];

    // Subtract all four components
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];

    // Restore the 4th component (only x,y,z are modified)
    out[3] = origW;
}