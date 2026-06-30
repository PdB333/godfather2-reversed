// FUNC_NAME: BuildTransformMatrix
// Address: 0x00557660
// Constructs a 4x4 transformation matrix from a source matrix by copying the 3x3 rotation and translation,
// setting the last column (indices 3,7,11) to zero and the w component (index15) from a global constant.
// Then calls a function FUN_00aa1a80 (likely a matrix setter or transform handler) with the result.

void BuildTransformMatrix(float* param_1)
{
    // Local matrix array in row-major order: [row0col0..row0col3, row1col0..row1col3, ...]
    float localMat[16];
    
    // Copy rotation part (3x3) from source
    localMat[0] = param_1[0];  // row0 col0
    localMat[1] = param_1[1];  // row0 col1
    localMat[2] = param_1[2];  // row0 col2
    localMat[3] = 0.0f;       // row0 col3 -> zero (no translation contribution)
    
    localMat[4] = param_1[4];  // row1 col0
    localMat[5] = param_1[5];  // row1 col1
    localMat[6] = param_1[6];  // row1 col2
    localMat[7] = 0.0f;       // row1 col3 -> zero
    
    localMat[8] = param_1[8];  // row2 col0
    localMat[9] = param_1[9];  // row2 col1
    localMat[10] = param_1[10];// row2 col2
    localMat[11] = 0.0f;      // row2 col3 -> zero
    
    // Copy translation part (row3)
    localMat[12] = param_1[12]; // row3 col0 (x translation)
    localMat[13] = param_1[13]; // row3 col1 (y translation)
    localMat[14] = param_1[14]; // row3 col2 (z translation)
    
    // Set w component from global constant (likely 1.0f for homogeneous coordinates)
    localMat[15] = *(float*)0x00e2b1a4;
    
    // Call the function that uses this matrix (e.g., setTransform, multiply, etc.)
    FUN_00aa1a80(localMat);
}