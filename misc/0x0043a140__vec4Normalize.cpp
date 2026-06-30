// FUNC_NAME: vec4Normalize
// Address: 0x0043a140
// Purpose: Normalize a 4-component vector (e.g., quaternion) with zero-length protection.
// Returns the original length of the input vector.

float vec4Normalize(const float* in, float* out)
{
    float lenSq = in[0] * in[0] + in[1] * in[1] + in[2] * in[2] + in[3] * in[3];
    float len, invLen;
    if (lenSq <= DAT_00e2cbe0) {  // epsilon squared (very small threshold)
        invLen = 0.0f;
        len = 0.0f;
    }
    else {
        len = sqrtf(lenSq);
        invLen = DAT_00e2b1a4 / len;  // DAT_00e2b1a4 is likely 1.0f
    }
    out[0] = in[0] * invLen;
    out[1] = in[1] * invLen;
    out[2] = in[2] * invLen;
    out[3] = in[3] * invLen;
    return len;
}