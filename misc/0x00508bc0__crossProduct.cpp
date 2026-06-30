// FUNC_NAME: crossProduct
void __fastcall crossProduct(float *out, const float *vecA, const float *vecB)
{
    // Compute cross product of 3D vector components (vecB x vecA), preserving out's original w.
    float savedW = out[3];
    out[0] = vecB[1] * vecA[2] - vecB[2] * vecA[1];
    out[1] = vecB[2] * vecA[0] - vecB[0] * vecA[2];
    out[2] = vecB[0] * vecA[1] - vecB[1] * vecA[0];
    out[3] = savedW; // restore original 4th component
}