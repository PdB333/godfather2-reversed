// FUNC_NAME: scale6ElementVector
// Function at 0x0052faa0: Multiplies each of 6 floats (in a vector) by a scalar.
// Used in EA EARS engine for scaling a 6-element vector (e.g., position+scale or custom data).
void scale6ElementVector(float* vec, float scalar)
{
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
    vec[3] *= scalar;
    vec[4] *= scalar;
    vec[5] *= scalar;
}