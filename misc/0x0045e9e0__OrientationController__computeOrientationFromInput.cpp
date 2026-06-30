// FUNC_NAME: OrientationController::computeOrientationFromInput
// Function at 0x0045e9e0: computes an orientation matrix from input state and transforms a reference vector
// This function appears to handle controller/stick input to compute a rotation matrix (param_2)
// and then apply it to a linear combination of vectors to produce an output quaternion/vector (param_1)
// The exact purpose is unclear, but likely converts some analog input (stick angles) into a 3D orientation.

// Assumptions:
// - param_1 and param_2 are float arrays (param_2 is a 4x4 matrix in row-major order)
// - Local stack variables form a quaternion (local_c4..local_d0) and a vector (local_c0, fStack_bc, fStack_b8)
// - Global constants: DAT_00e44598 (threshold), DAT_00e44680 (mask), DAT_00e2b1a4 (one?), DAT_00e2cbe0 (epsilon for quaternion length)

undefined4 __thiscall OrientationController::computeOrientationFromInput(float *outputVecOrQuat, float *matrix4x4)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    char inputValid;
    float scale;
    float squaredLen;
    undefined4 retVal;
    
    // Quaternion components (stack offsets: -0xd0, -0xcc, -0xc8, -0xc4)
    float quatW;  // local_d0
    float quatZ;  // local_cc
    float quatY;  // local_c8
    float quatX;  // local_c4
    
    // Vector components from input state (stack offsets: -0xc0, -0xbc, -0xb8)
    float inputVecX;  // local_c0
    float inputVecY;  // fStack_bc
    float inputVecZ;  // fStack_b8
    
    // Misc locals
    uint inputBits0;  // local_b0
    uint inputBits1;  // local_ac
    uint inputBits2;  // local_a8
    float inputFloat; // local_a4
    
    // Initialize output and temporaries
    retVal = 0;
    inputVecZ = 0.0;
    inputVecY = 0.0;
    inputVecX = 0.0;
    
    // Step 1: Read input state (likely from controller) and extract initial vector and bit fields
    inputValid = readInputState(&inputVecX, &inputBits0);    // FUN_0045ec00
    if (inputValid != 0)
    {
        // Check if any of the input bits indicate significant magnitude
        // The float threshold DAT_00e44598 is compared against bitwise-AND results (probably float as bits?)
        // This is a peculiar pattern – likely extracting specific bits that encode magnitude
        if ((((DAT_00e44598 <= (float)(inputBits0 & DAT_00e44680)) ||
              (DAT_00e44598 <= (float)(inputBits1 & DAT_00e44680))) ||
             (DAT_00e44598 <= (float)(inputBits2 & DAT_00e44680))) ||
            (DAT_00e44598 <= (float)((uint)(inputFloat - DAT_00e2b1a4) & DAT_00e44680)))
        {
            // Input has sufficient magnitude – compute quaternion from the input state
            // Initialize identity elements (matrix[15]=1, others=0) – not shown fully
            inputFloat = DAT_00e2b1a4;  // Reference value (probably 1.0f)
            // Clear matrix to identity? (stack locals used elsewhere)
            setIdentityMatrix(matrix4x4);                     // FUN_00470f80 (likely sets matrix to identity)
            copyMatrixAligned(local_50, matrix4x4);           // FUN_0044b4e0 – possibly copy to a temporary
            quatFromInputState(local_50, tmpQuat);            // FUN_0056d530 – convert matrix/input to quaternion
            extractQuaternionFromBits(tmpQuat, &inputBits0, &quatW); // FUN_0056cba0 – builds quaternion from bit fields and writes to quatW..quatX
            
            // Normalize quaternion
            squaredLen = quatX * quatX + quatY * quatY + quatZ * quatZ + quatW * quatW;
            if (squaredLen <= DAT_00e2cbe0)
            {
                scale = 0.0f;
            }
            else
            {
                scale = DAT_00e2b1a4 / sqrtf(squaredLen);
            }
            quatW *= scale;
            quatZ *= scale;
            quatY *= scale;
            quatX *= scale;
            
            // Convert quaternion to rotation matrix and store in matrix4x4
            quatToMatrix(&quatW, matrix4x4);                  // FUN_0056cef0
            // Set the translation part of the matrix to zero (pure rotation)
            matrix4x4[12] = 0.0f;   // row 3, col 0
            matrix4x4[13] = 0.0f;   // row 3, col 1
            matrix4x4[14] = 0.0f;   // row 3, col 2
            matrix4x4[15] = 1.0f;   // row 3, col 3 (identity)
        }
        else
        {
            // Input magnitude too small – set matrix to identity
            setIdentityMatrix(matrix4x4);                     // FUN_00470f80
        }
        
        // Now transform a vector using the rotation matrix
        // The matrix is row-major: columns are at indices 0,4,8; rows are 0-3,4-7,8-11
        // The vector being transformed is (inputVecX, inputVecY, inputVecZ) but coefficients are reordered:
        // result = col0 * inputVecX + col1 * inputVecY + col2 * inputVecZ
        // This is effectively rotating the vector by the matrix.
        fVar1 = matrix4x4[5];  // row1, col1 (0-based row1 = index 4..7)
        fVar2 = matrix4x4[6];  // row1, col2
        fVar3 = matrix4x4[7];  // row1, col3
        fVar4 = matrix4x4[1];  // row0, col1
        fVar5 = matrix4x4[2];  // row0, col2
        fVar6 = matrix4x4[3];  // row0, col3
        fVar11 = outputVecOrQuat[3];  // Backup the original fourth component (may be preserved)
        fVar7 = matrix4x4[9];  // row2, col1
        fVar8 = matrix4x4[10]; // row2, col2
        fVar9 = matrix4x4[11]; // row2, col3
        
        // Compute each component of the rotated vector
        outputVecOrQuat[0] = inputVecZ * matrix4x4[4] + inputVecX * matrix4x4[0] + inputVecY * matrix4x4[8];
        outputVecOrQuat[1] = inputVecZ * fVar1    + inputVecX * fVar4    + inputVecY * fVar7;
        outputVecOrQuat[2] = inputVecZ * fVar2    + inputVecX * fVar5    + inputVecY * fVar8;
        outputVecOrQuat[3] = fVar11;   // Restore the original fourth value (e.g., w component)
        
        return 1;  // Success
    }
    return 0;  // No valid input
}