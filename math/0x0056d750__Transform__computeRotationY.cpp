// FUNC_NAME: Transform::computeRotationY
void Transform::computeRotationY(float angleDeg, float* outMatrix)
{
    // outMatrix is expected to be a float[4] row-major 2x2 matrix or quaternion?
    // Assumes outMatrix[1] and outMatrix[2] are set to zero (identity off-diagonals)
    outMatrix[1] = 0.0f;
    outMatrix[2] = 0.0f;

    // Convert degrees to radians using global constant
    float angleRad = angleDeg * g_degreesToRadians;
    double temp = (double)angleRad;

    // Compute cos(angleRad) using FPU-based function
    cosFromFPU(); // likely inline asm fcos
    outMatrix[0] = (float)temp; // cos

    // Re-evaluate angle (or reuse?) - double conversion triggers second call
    temp = (double)angleRad;
    sinFromFPU(); // likely inline asm fsin
    outMatrix[3] = (float)temp; // sin
}