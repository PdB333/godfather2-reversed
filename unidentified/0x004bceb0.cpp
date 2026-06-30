// FUNC_004bceb0: vector3NormalizeToLength - Normalizes a 3D vector to a fixed target length if its squared magnitude exceeds a minimum threshold; otherwise outputs zero.

void vector3NormalizeToLength(float *out, const float *in) // in passed via EAX (fastcall), out on stack
{
    float lengthSquared = in[0]*in[0] + in[1]*in[1] + in[2]*in[2];
    float scale;

    // Threshold constant from global data (likely kMinSquaredLength)
    if (lengthSquared <= g_kMinSquaredLength) { // DAT_00e2cbe0
        scale = 0.0f;
    } else {
        // Target length constant from global data (likely kTargetLength)
        scale = g_kTargetLength / __sqrt(lengthSquared); // DAT_00e2b1a4
    }

    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
}