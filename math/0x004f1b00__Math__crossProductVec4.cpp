// FUNC_NAME: Math::crossProductVec4
void __fastcall crossProductVec4(float* dest, const float* v1, const float* v2) // dest (in EAX), v1 (param_2), v2 (param_3)
{
    // Computes cross product: dest = v2 x v1 (component order swapped for standard cross)
    // Preserves dest[3] (w component) unchanged.
    float destW = dest[3];
    dest[0] = v2[1] * v1[2] - v2[2] * v1[1]; // cross x
    dest[1] = v2[2] * v1[0] - v2[0] * v1[2]; // cross y
    dest[2] = v2[0] * v1[1] - v2[1] * v1[0]; // cross z
    dest[3] = destW; // restore original w
}