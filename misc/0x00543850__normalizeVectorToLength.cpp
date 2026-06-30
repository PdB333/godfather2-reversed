// FUNC_NAME: normalizeVectorToLength
// Function at 0x00543850: Normalizes a 4‑component vector (x,y,z,w) to a fixed length
// The length is computed from the first three components (x,y,z) and scaled by a global constant (DAT_00e2b1a4).
// All four components are scaled uniformly.

void __fastcall normalizeVectorToLength(float* vec) {
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];
    float w = vec[3];

    // Compute the Euclidean length of the 3D vector (x,y,z)
    float lengthSquared = x * x + y * y + z * z;
    float length = sqrtf(lengthSquared);   // FUN_00414a80 is likely sqrt

    // Scale factor = targetLength / currentLength
    // DAT_00e2b1a4 is the target length (e.g., 1.0f for unit vector)
    float factor = DAT_00e2b1a4 / length;

    vec[0] = x * factor;
    vec[1] = y * factor;
    vec[2] = z * factor;
    vec[3] = w * factor;   // w component also scaled (homogeneous coordinate or padding)
}