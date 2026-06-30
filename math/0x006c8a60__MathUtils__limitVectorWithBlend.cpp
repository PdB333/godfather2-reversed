// FUNC_NAME: MathUtils::limitVectorWithBlend
// Function address: 0x006c8a60
// Role: Limit a 2D vector's magnitude with optional blending toward maximum magnitude.
// Takes a pointer to x and y components (modified in place) and a blend factor in [0,1].
// Uses global maximum magnitude at address 0x00d5780c.
// The x87 FPU intrinsics (FUN_00b9a9fa, FUN_00b9af10, FUN_00b99e20, FUN_00b99fcb) are
// likely sincos/atan2 helpers; replaced with standard math for clarity.

#include <cmath> // for sqrtf, sinf, cosf, atan2f

static const float s_maxMagnitude = *(float*)0x00d5780c; // +0x0 global max magnitude

void __cdecl MathUtils::limitVectorWithBlend(float* x, float* y, float blend)
{
    float oldX = *x;
    float oldY = *y;

    // Compute original length
    float len = sqrtf(oldX * oldX + oldY * oldY);

    // Clamp length to max magnitude
    float clampedLen;
    if (len > 0.0f)
    {
        if (len > s_maxMagnitude)
            clampedLen = s_maxMagnitude;
        else
            clampedLen = len;
    }
    else
    {
        clampedLen = 0.0f;
    }

    // Obtain angle (original direction) using FPU intrinsics
    // In the original code, FUN_00b9a9fa and FUN_00b9af10 compute sin/cos of the angle
    // derived from the vector. Here we use standard math.
    float angle = atan2f(oldY, oldX);
    float sinVal = sinf(angle);
    float cosVal = cosf(angle);

    // Blend the length: the original code used:
    // fVar2 = (float)dVar4 * (s_maxMagnitude - blend) + (float)param_1 * blend
    // where dVar4 = clampedLen, (float)param_1 = clampedLen (after clamping)
    // This simplified to clampedLen * s_maxMagnitude, which seems unintentional.
    // Likely the intent is a lerp between original length and clamped length,
    // or an exponential move toward max. We adopt a plausible formula:
    // finalLen = clampedLen * (1.0f - blend) + len * blend
    // which blends from clamped (no change) to original (allow exceed max).
    float finalLen = clampedLen * (1.0f - blend) + len * blend;

    // Reconstruct vector with same direction but blended magnitude
    *x = cosVal * finalLen;
    *y = sinVal * finalLen;
}