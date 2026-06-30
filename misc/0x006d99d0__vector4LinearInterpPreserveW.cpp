// FUNC_NAME: vector4LinearInterpPreserveW
// Address: 0x006d99d0
// Role: Interpolates xyz components of a 4D vector (a) towards (b) by factor t,
// but preserves the original w component of the output vector unchanged.
// Used for position interpolation where w holds metadata (e.g., type flag).

void __fastcall vector4LinearInterpPreserveW(float* out, const float* a, const float* b, float t)
{
    // Save output's w component before modification
    float originalW = out[3];

    // Interpolate x, y, z using standard linear blend: result = a * t + b
    out[0] = t * a[0] + b[0];
    out[1] = t * a[1] + b[1];
    out[2] = t * a[2] + b[2];

    // Interpolate w (will be overwritten)
    out[3] = t * a[3] + b[3];

    // Restore original w – keeping the component unchanged
    out[3] = originalW;
}