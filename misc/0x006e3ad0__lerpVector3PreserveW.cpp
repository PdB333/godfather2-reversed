// FUNC_NAME: lerpVector3PreserveW
void __fastcall lerpVector3PreserveW(float *out, int unusedParam, float *start, float *end, float t)
{
    float startY = start[1];
    float startZ = start[2];
    float startW = start[3];
    float endY = end[1];
    float endZ = end[2];
    float endW = end[3];
    float origOutW = out[3]; // preserve original W component

    // Lerp only X, Y, Z components; W is restored from original output value
    out[0] = (end[0] - start[0]) * t + start[0];
    out[1] = (endY - startY) * t + startY;
    out[2] = (endZ - startZ) * t + startZ;
    out[3] = (endW - startW) * t + startW; // computed but immediately overwritten
    out[3] = origOutW; // restore original W, effectively skipping W interpolation
}