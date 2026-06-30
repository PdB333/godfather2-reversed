// FUNC_NAME: scaleVectorToLength
// Address: 0x0056d2c0
// Takes a direction vector (x, y, z) and a scalar (w), and outputs a vector where
// the first three components are scaled to have length = scalar * g_globalScaleFactor,
// and the fourth component is that length. Essentially creates a vector with given
// direction and scaled magnitude.
void scaleVectorToLength(float x, float y, float z, float w, float* outVec)
{
    // Global scale factor (likely from data section)
    float globalScale = *reinterpret_cast<float*>(0x00e2cd54); // DAT_00e2cd54

    // Apply global scale to the scalar
    w = w * globalScale;

    // Store direction components and the scaled scalar temporarily
    outVec[0] = x;
    outVec[1] = y;
    outVec[2] = z;
    outVec[3] = w;

    // Save the scaled scalar before later scaling
    float savedW = outVec[3];

    // Note: The following calls (FUN_00b99e20 and FUN_00b99fcb) are likely
    // compiler helper functions for floating-point conversions (e.g., x87 stack management).
    // They don't affect the logical result, so they are omitted here.
    // FUN_00b99e20(); // possibly __ftol2 or similar
    // FUN_00b99fcb(); // possibly __fltused or similar

    // Compute the magnitude of the direction vector
    float magSq = x * x + y * y + z * z;
    float magnitude = sqrt(magSq);

    // Scale factor to adjust the direction components to the desired length
    float scale = w / magnitude;

    // Scale all four components
    outVec[0] = outVec[0] * scale;
    outVec[1] = outVec[1] * scale;
    outVec[2] = outVec[2] * scale;
    outVec[3] = outVec[3] * scale;

    // Restore the fourth component to the original scaled scalar (unscaled by direction magnitude)
    outVec[3] = savedW;
}