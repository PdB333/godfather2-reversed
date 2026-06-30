// FUNC_NAME: vector4Normalize
// Normalizes a 4-component vector (x,y,z,w) using squared length of first three components.
// If length is zero, sets inverse to zero, resulting in zero vector (w becomes 0).
// Uses an external sqrt function (likely x87 fsqrt).
void __fastcall vector4Normalize(float* vec4)
{
    float x = vec4[0]; // +0x00
    float y = vec4[1]; // +0x04
    float z = vec4[2]; // +0x08
    float w = vec4[3]; // +0x0C

    float lenSq = x * x + y * y + z * z;
    float invLen;

    if (lenSq == 0.0f) {
        invLen = 0.0f;
    } else {
        float len = (float)FUN_00414a80(lenSq); // sqrt(lenSq) using extended precision
        invLen = 1.0f / len;
    }

    vec4[0] = x * invLen;
    vec4[1] = y * invLen;
    vec4[2] = z * invLen;
    vec4[3] = w * invLen;
}