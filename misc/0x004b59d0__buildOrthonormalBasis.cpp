// FUNC_NAME: buildOrthonormalBasis
// Function at 0x004b59d0: Constructs an orthonormal basis from three 4D vectors (first two are normalized, third computed as cross product).
// Input param_1: pointer to 12 floats representing rows of a 3x4 matrix (each row has X, Y, Z, W where W is ignored and set to 0).
// Output param_2: pointer to 12 floats where result is written.
// The function copies the data, normalizes the first two rows (ignoring W), then computes the third row as cross product of the first two.
void buildOrthonormalBasis(float* input, float* output)
{
    // Copy first row (X, Y, Z, W) where W set to 0
    float x0 = input[0];
    float y0 = input[1];
    float z0 = input[2];
    output[0] = x0;
    output[1] = y0;
    output[2] = z0;
    output[3] = 0.0f; // W component set to zero

    // Copy second row
    float x1 = input[4];
    float y1 = input[5];
    float z1 = input[6];
    output[4] = x1;
    output[5] = y1;
    output[6] = z1;
    output[7] = 0.0f; // W

    // Copy third row
    float x2 = input[8];
    float y2 = input[9];
    float z2 = input[10];
    output[8] = x2;
    output[9] = y2;
    output[10] = z2;
    output[11] = 0.0f; // W

    // Normalize first row (X, Y, Z only)
    float lenSq0 = output[0]*output[0] + output[1]*output[1] + output[2]*output[2];
    float invLen0;
    if (lenSq0 == 0.0f) {
        invLen0 = 0.0f;
    } else {
        invLen0 = 1.0f / sqrtf(lenSq0);
    }
    output[0] *= invLen0;
    output[1] *= invLen0;
    output[2] *= invLen0;
    output[3] *= invLen0; // still zero

    // Normalize second row (X, Y, Z only)
    float lenSq1 = output[4]*output[4] + output[5]*output[5] + output[6]*output[6];
    float invLen1;
    if (lenSq1 == 0.0f) {
        invLen1 = 0.0f;
    } else {
        invLen1 = 1.0f / sqrtf(lenSq1);
    }
    output[4] *= invLen1;
    output[5] *= invLen1;
    output[6] *= invLen1;
    output[7] *= invLen1; // still zero

    // Compute third row as cross product of first two rows
    // cross = first × second = (y0*z1 - z0*y1, z0*x1 - x0*z1, x0*y1 - y0*x1)
    output[8] = output[1]*output[6] - output[2]*output[5];
    output[9] = output[2]*output[4] - output[0]*output[6];
    output[10] = output[0]*output[5] - output[1]*output[4];
    output[11] = 0.0f; // W still zero
}