// FUNC_NAME: vec3Sub
void __fastcall vec3Sub(float *out, const float *a, const float *b)
{
    // Subtract two 4-component vectors, preserving the 4th component of the output.
    // This is effectively a 3D vector subtraction (x,y,z) with w left unchanged.
    float aY = a[1];
    float aZ = a[2];
    float aW = a[3];
    float bY = b[1];
    float bZ = b[2];
    float bW = b[3];
    float savedW = out[3]; // Save original w component

    out[0] = a[0] - b[0]; // x
    out[1] = aY - bY;     // y
    out[2] = aZ - bZ;     // z
    out[3] = aW - bW;     // w difference (temporary)
    out[3] = savedW;      // Restore original w, effectively ignoring the w subtraction
}