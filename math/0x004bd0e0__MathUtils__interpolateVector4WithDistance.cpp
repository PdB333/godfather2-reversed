// FUNC_NAME: MathUtils::interpolateVector4WithDistance
// Function at 0x004bd0e0: Performs a linear interpolation (lerp) between two Vector4 objects (from and to) using a global factor,
// storing the result in 'out', and sets the 'w' component to the length of the (scaled) displacement vector (dx, dy, dz).
// The interpolation factor is stored in the global float DAT_00e2cd54 (likely time step or smoothing constant).
// Indices: 0=x, 1=y, 2=z, 3=w.

// Global interpolation factor (from Ghidra data reference)
extern const float g_interpolationFactor; // DAT_00e2cd54

void interpolateVector4WithDistance(float* out, const float* from, const float* to)
{
    // Compute scaled difference: (to - from) * factor
    float dx = (to[0] - from[0]) * g_interpolationFactor;
    float dy = (to[1] - from[1]) * g_interpolationFactor;
    float dz = (to[2] - from[2]) * g_interpolationFactor;
    float dw = (to[3] - from[3]) * g_interpolationFactor;

    // Store scaled difference temporarily in out
    out[0] = dx;
    out[1] = dy;
    out[2] = dz;
    out[3] = dw;

    // Compute length of the (dx,dy,dz) vector (ignoring dw)
    float displacementLength = sqrtf(dx*dx + dy*dy + dz*dz);
    out[3] = displacementLength;

    // Lerp the first three components: out = from + (out) = from + (to - from) * factor
    out[0] = from[0] + out[0];
    out[1] = from[1] + out[1];
    out[2] = from[2] + out[2];
    out[3] = from[3] + out[3];

    // Override w to the displacement length (final w is not a lerp but the distance)
    out[3] = displacementLength;
}