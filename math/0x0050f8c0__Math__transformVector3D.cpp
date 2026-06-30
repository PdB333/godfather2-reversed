// FUNC_NAME: Math::transformVector3D
void Math::transformVector3D(float *result, float *matrix, float *vector)
{
    // Perform matrix-vector multiplication for a 3D transformation
    // matrix is a 3x3 matrix stored row-major: matrix[0..2] = row0, matrix[3..5] = row1, matrix[6..8] = row2
    // vector is the input vector (x, y, z)
    // result is the output vector (x, y, z)
    
    // Call to a helper function (likely gets/sets FPU rounding mode or similar)
    FUN_004e41b0();
    
    // Compute x component: vector->x * matrix[0][0] + matrix[0][3] (translation?)
    // Actually: *unaff_EDI = matrix row0, *param_1 = vector x, *unaff_ESI = result x
    // in_XMM0_Da = vector->x (passed via XMM0)
    float fVar1 = in_XMM0_Da * *unaff_EDI + *param_1;
    *unaff_ESI = fVar1;
    
    FUN_004e41b0();
    
    // Compute y component: previous result * matrix[1][0] + vector->y
    // unaff_EDI[1] = matrix row1 col0? Actually row1 col0 = matrix[3]
    // param_1[1] = vector->y
    fVar1 = fVar1 * unaff_EDI[1] + param_1[1];
    unaff_ESI[1] = fVar1;
    
    FUN_004e41b0();
    
    // Compute z component: previous result * matrix[2][0] + vector->z
    // unaff_EDI[2] = matrix row2 col0 = matrix[6]
    // param_1[2] = vector->z
    unaff_ESI[2] = fVar1 * unaff_EDI[2] + param_1[2];
    
    return;
}