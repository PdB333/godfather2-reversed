// FUNC_NAME: crossProduct
// Function address: 0x00501820
// Computes the cross product of two 4-element vectors (only first 3 components used, fourth set to 0).
// Likely a math utility from EA EARS engine.
void crossProduct(const float* vectorA, const float* vectorB, float* result) {
    float a0 = vectorA[0];
    float a1 = vectorA[1];
    float a2 = vectorA[2];
    float a3 = vectorA[3]; // ignored in cross, but used for zeroing result's w
    float b0 = vectorB[0];
    float b1 = vectorB[1];
    float b2 = vectorB[2];
    float b3 = vectorB[3]; // ignored

    result[0] = a1 * b2 - a2 * b1; // cross x
    result[1] = a2 * b0 - a0 * b2; // cross y
    result[2] = a0 * b1 - a1 * b0; // cross z
    result[3] = 0.0f; // w component set to zero
}