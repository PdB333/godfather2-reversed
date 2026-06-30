// FUNC_NAME: normalizeVec3WithW
void __fastcall normalizeVec3WithW(float* vec)
{
    // Normalize a 4-component vector using the 3D Euclidean length (x,y,z).
    // The fourth component is scaled proportionally.
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];

    // Compute length of (x,y,z)
    float lenSq = x * x + y * y + z * z;
    float len = sqrtf(lenSq); // FUN_00414a80 is sqrtf

    // Scale factor: assume DAT_00e2b1a4 is 1.0f
    float invLen = 1.0f / len; // Equivalent to DAT_00e2b1a4 / len

    vec[0] = x * invLen;
    vec[1] = y * invLen;
    vec[2] = z * invLen;
    vec[3] = vec[3] * invLen;
}