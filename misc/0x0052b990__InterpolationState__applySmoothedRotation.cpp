// FUNC_NAME: InterpolationState::applySmoothedRotation

// Global interpolation state variables (from .data section)
// These are likely members of a singleton or module-level struct
static float s_divisor;         // DAT_01125280 - divisor for normalization, reset after use
static float s_accumTime;       // DAT_01125250 - accumulated time/weight
static float s_target;          // DAT_01125254 - some target value (angle? time?)
static float s_interpQuat[4];   // DAT_01125260-6c - quaternion or 4D vector (x,y,z,w) being interpolated
static int s_interpFlags;       // DAT_01125270 - bit flags: bit0 active, bit1 etc.
static const float s_one = 1.0f; // DAT_00e2b1a4 - constant 1.0 (or identity value)

// Forward declaration of the underlying smoothing routine
// Parameters: quatOut, accumTime, target, flags..., then zeros
void smoothingFunc(float* quat, float accumTime, float target, 
                   int flag0, int flag1, int zero, int zero2, int zero3);

void InterpolationState::applySmoothedRotation()
{
    // Guard: only process if divisor is non-zero and we have accumulated time & target
    if (s_divisor != 0.0f && s_accumTime > 0.0f && s_target != 0.0f)
    {
        // Normalize the interpolated quaternion by the divisor (weight sum or time delta)
        float factor = s_one / s_divisor;
        s_interpQuat[0] *= factor;
        s_interpQuat[1] *= factor;
        s_interpQuat[2] *= factor;
        s_interpQuat[3] *= factor;

        // Call the actual smoothing/application routine
        // - s_interpQuat: the normalized quaternion
        // - s_accumTime: accumulated time (or weight)
        // - s_target: target value (maybe angle or intensity)
        // - flags extracted from s_interpFlags: bit0 and bit1 (note: bit1 is shifted and masked)
        FUN_0052cbd0(s_interpQuat,
                     s_accumTime,
                     s_target,
                     s_interpFlags & 1,                 // flag0 = lowest bit
                     (s_interpFlags >> 1) & 0xffffff01, // flag1 = bit1, then masked oddly (likely only LSB kept)
                     0, 0, 0);

        // Clear the low two flag bits (reset state)
        s_interpFlags &= 0xfffffffc; // ~0x03

        // Reset accumulated state
        s_accumTime = 0.0f;
        s_target = 0.0f;

        // Reset quaternion to identity (x=y=z=1, w=0?) – note: probably means rotation identity (1,0,0,0) but code sets x,y,z to 1, w to 0
        s_interpQuat[0] = s_one;  // 1.0
        s_interpQuat[1] = s_one;  // 1.0
        s_interpQuat[2] = s_one;  // 1.0
        s_interpQuat[3] = 0.0f;

        // Clear divisor to prevent re-entry
        s_divisor = 0.0f;
    }
}