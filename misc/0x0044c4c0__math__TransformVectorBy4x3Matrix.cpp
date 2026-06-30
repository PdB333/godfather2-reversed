// FUNC_NAME: math::TransformVectorBy4x3Matrix
void TransformVectorBy4x3Matrix(const float* matrix, const float* inVec, float* outVec) {
    // matrix is a 4x3 matrix stored in column-major order (4 rows, 3 columns)
    // Indices: column0: 0,1,2,3; column1: 4,5,6,7; column2: 8,9,10,11
    // This transforms a 3D point (inVec: x,y,z) -> outVec (x,y,z,w) where w is preserved.
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];
    float originalW = outVec[3]; // preserve w component

    // Compute output x,y,z as dot product of input vector with each row of the 4x3 matrix
    outVec[0] = x * matrix[0] + y * matrix[4] + z * matrix[8];
    outVec[1] = x * matrix[1] + y * matrix[5] + z * matrix[9];
    outVec[2] = x * matrix[2] + y * matrix[6] + z * matrix[10];
    // The computed w (from row3) is discarded; original w is restored.
    outVec[3] = originalW;
}