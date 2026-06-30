// FUNC_NAME: Vector4::lerpPosition
void __fastcall Vector4::lerpPosition(float *outVector, const float *from, const float *to, float t)
{
    // outVector is this (in EAX), from is param_2 (often a vector), to is param_3, t is param_4
    // Performs linear interpolation of first 3 components (x,y,z) but preserves the 4th component (w)
    float wOriginal = outVector[3]; // save original w

    outVector[0] = (to[0] - from[0]) * t + from[0]; // x
    outVector[1] = (to[1] - from[1]) * t + from[1]; // y
    outVector[2] = (to[2] - from[2]) * t + from[2]; // z
    outVector[3] = wOriginal; // restore w unchanged
}