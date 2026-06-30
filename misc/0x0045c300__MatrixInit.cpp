// FUNC_NAME: MatrixInit
// Function address: 0x0045c300
// Role: Initializes a 4x4 matrix (16 floats) by copying from source (mode 0) or constructing an identity-like matrix (mode 1,2). 
// The identity path sets specific elements (likely indices 3,4,5,6) to zeros and a global constant, then calls a helper function to fill the rest.

#include <cstdint>

// Global constant used in matrix initialization (interpreted as float)
extern const float g_identityConstant; // DAT_00e2b1a4

// Forward declaration of the helper function called during identity construction
void matrixFillIdentityHelper(); // FUN_00417560

/**
 * @brief Initializes a 4x4 matrix based on the given mode.
 * 
 * @param outMatrix Pointer to the destination 16-element float array.
 * @param inMatrix  Pointer to the source 16-element float array (used only for mode 0).
 * @param mode      0: copy from inMatrix; 1 or 2: construct identity matrix (same code for both).
 * @return outMatrix.
 */
float* MatrixInit(float* outMatrix, float* inMatrix, int32_t mode) {
    float tempMatrix[16]; // Temporary matrix for identity construction

    if (mode == 0) {
        // Copy 16 floats from source to destination
        for (int32_t i = 0; i < 16; ++i) {
            outMatrix[i] = inMatrix[i];
        }
        return outMatrix;
    }

    // Mode 1 and 2 (identical code)
    // Set specific elements of the temp matrix (offsets derived from decompiled locals):
    //   local_50[3] = 0.0f   -> tempMatrix[3]
    //   local_34    = 0.0f   -> tempMatrix[4] (assumed)
    //   local_24    = 0.0f   -> tempMatrix[5] (assumed)
    //   local_14    = DAT    -> tempMatrix[6] (assumed)
    // These four values are the initial part of the matrix diagonal?
    tempMatrix[3] = 0.0f;
    tempMatrix[4] = 0.0f;
    tempMatrix[5] = 0.0f;
    tempMatrix[6] = g_identityConstant;

    // Call helper to fill remaining elements (likely sets rest to identity or zero)
    matrixFillIdentityHelper();

    // Copy the constructed temp matrix to the output
    for (int32_t i = 0; i < 16; ++i) {
        outMatrix[i] = tempMatrix[i];
    }

    return outMatrix;
}