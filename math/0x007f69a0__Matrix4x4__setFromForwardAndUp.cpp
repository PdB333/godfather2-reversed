//FUNC_NAME: Matrix4x4::setFromForwardAndUp
// Function at 0x007f69a0: Builds a 4x4 rotation matrix from a forward vector and a reference up matrix.
// Uses global constants: g_fOne (0x00d5780c) = 1.0f, g_uiAbsMask (0x00e44680) = 0x7FFFFFFF for absolute value comparison.

#include <cmath> // for fabs? Not used directly, but for clarity

// Forward declarations of helper functions (likely in math library)
void normalizeVector3(float* vec); // FUN_0056afa0 - normalizes a 3-component vector in-place
void normalizeVector3(float* vec); // FUN_0043a2a0 - same function (duplicate call)

void Matrix4x4::setFromForwardAndUp(float* outMatrix, const float* refMatrix, const float* forward)
{
    // outMatrix is a 4x4 matrix stored row-major (16 floats)
    // refMatrix is a 4x4 matrix (only first two rows of rotation part used)
    // forward is a 3D vector

    float fOne = *(float*)0x00d5780c; // typically 1.0f
    unsigned int absMask = *(unsigned int*)0x00e44680; // 0x7FFFFFFF

    // Initialize outMatrix to identity
    outMatrix[0] = fOne;
    outMatrix[1] = 0.0f;
    outMatrix[2] = 0.0f;
    outMatrix[3] = 0.0f;
    outMatrix[4] = 0.0f;
    outMatrix[5] = fOne;
    outMatrix[6] = 0.0f;
    outMatrix[7] = 0.0f;
    outMatrix[8] = 0.0f;
    outMatrix[9] = 0.0f;
    outMatrix[10] = fOne;
    outMatrix[11] = 0.0f;
    outMatrix[12] = 0.0f;
    outMatrix[13] = 0.0f;
    outMatrix[14] = 0.0f;
    outMatrix[15] = fOne;

    // Copy forward vector and normalize it
    float fwdX = forward[0];
    float fwdY = forward[1];
    float fwdZ = forward[2];
    normalizeVector3(&fwdX); // FUN_0056afa0

    // Set the forward direction (row2 of rotation part) to normalized forward
    outMatrix[8] = fwdX;
    outMatrix[9] = fwdY;
    outMatrix[10] = fwdZ;

    // Compute dot products with refMatrix rows to decide which axis to use for cross product
    // refMatrix rows: row0 = [refMatrix[0], refMatrix[1], refMatrix[2]]
    //                row1 = [refMatrix[4], refMatrix[5], refMatrix[6]]
    float dotRow0 = fwdX * refMatrix[0] + fwdY * refMatrix[1] + fwdZ * refMatrix[2];
    float dotRow1 = fwdX * refMatrix[4] + fwdY * refMatrix[5] + fwdZ * refMatrix[6];

    // Compare absolute values using bitwise AND with absMask
    if ((*(unsigned int*)&dotRow1 & absMask) < (*(unsigned int*)&dotRow0 & absMask))
    {
        // Use refMatrix row1 (up) to compute right vector via cross product
        float rightX = refMatrix[5] * fwdZ - refMatrix[6] * fwdY;
        float rightY = refMatrix[6] * fwdX - refMatrix[4] * fwdZ;
        float rightZ = fwdY * refMatrix[4] - fwdX * refMatrix[5];

        outMatrix[0] = rightX;
        outMatrix[1] = rightY;
        outMatrix[2] = rightZ;

        // Compute up vector as cross product of right and forward
        outMatrix[4] = rightZ * fwdY - outMatrix[1] * fwdZ;
        outMatrix[5] = outMatrix[0] * fwdZ - rightZ * fwdX;
        outMatrix[6] = outMatrix[1] * fwdX - outMatrix[0] * fwdY;

        normalizeVector3(outMatrix); // FUN_0043a2a0 - normalizes the first 3 components? Actually normalizes the whole matrix? Probably normalizes the first 3 floats (right vector) but code passes outMatrix pointer, so it normalizes the first 3 floats as a vector.
        // Note: The original code calls FUN_0043a2a0(param_1, param_1) which likely normalizes the vector at param_1 (first 3 floats).
    }
    else
    {
        // Use refMatrix row0 (right) to compute up vector via cross product
        float upX = fwdY * refMatrix[2] - refMatrix[1] * fwdZ;
        float upY = fwdZ * refMatrix[0] - fwdX * refMatrix[2];
        float upZ = fwdX * refMatrix[1] - fwdY * refMatrix[0];

        outMatrix[4] = upX;
        outMatrix[5] = upY;
        outMatrix[6] = upZ;

        // Compute right vector as cross product of up and forward
        outMatrix[0] = outMatrix[5] * fwdZ - upZ * fwdY;
        outMatrix[1] = outMatrix[6] * fwdX - upX * fwdZ;
        outMatrix[2] = upX * fwdY - outMatrix[5] * fwdX;

        normalizeVector3(outMatrix); // FUN_0043a2a0
    }
}