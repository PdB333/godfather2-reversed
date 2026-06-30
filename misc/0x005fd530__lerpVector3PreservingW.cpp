// FUNC_NAME: lerpVector3PreservingW
// Function address: 0x005fd530
// Performs 3D vector linear interpolation (x,y,z) while preserving the fourth component (w).
// This is used for interpolating positions (3 components) without modifying the homogeneous w.

void __fastcall lerpVector3PreservingW(float* out, float* from, float* to, float t)
{
    // Load 'from' components
    float fromY = from[1];
    float fromZ = from[2];
    float fromW = from[3]; // unused in final w calculation

    // Load 'to' components
    float toY = to[1];
    float toZ = to[2];
    float toW = to[3]; // unused in final w calculation

    float savedOutW = out[3]; // preserve original w of output vector

    // Interpolate x, y, z
    out[0] = (to[0] - from[0]) * t + from[0];
    out[1] = (toY - fromY) * t + fromY;
    out[2] = (toZ - fromZ) * t + fromZ;

    // Interpolate w (temporarily)
    out[3] = (toW - fromW) * t + fromW;

    // Restore original w – effectively only x,y,z are interpolated
    out[3] = savedOutW;
}