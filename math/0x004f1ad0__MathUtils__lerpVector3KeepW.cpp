// FUNC_NAME: MathUtils::lerpVector3KeepW
// Address: 0x004f1ad0
// Performs linear interpolation on first three components of a 4-float vector.
// Fourth component (index 3) is preserved from the output buffer.
// Uses __fastcall with ecx unused, edx = source A, stack = source B, t.
// Output pointer is passed in EAX (not in standard registers).

void __fastcall MathUtils::lerpVector3KeepW(float* out, float* a, float* b, float t)
{
    // // Save original output W component
    float savedW = out[3];
    
    // // Interpolate X, Y, Z (indices 0,1,2)
    out[0] = (b[0] - a[0]) * t + a[0];
    out[1] = (b[1] - a[1]) * t + a[1];
    out[2] = (b[2] - a[2]) * t + a[2];
    out[3] = savedW;   // // Restore original W component (no interpolation)
}