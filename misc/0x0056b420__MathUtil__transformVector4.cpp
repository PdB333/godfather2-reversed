// FUNC_NAME: MathUtil::transformVector4

// Performs a 4x4 matrix * 4-component vector multiplication (column-major storage).
// matrix: 16-element float array, column-major: column0 = [0,1,2,3], column1 = [4,5,6,7], column2=[8,9,10,11], column3=[12,13,14,15]
// inVector: 4-element input vector (x,y,z,w)
// outVector: 4-element output vector (result)
// This is the standard transformVector4 used in EA's math library for The Godfather 2.

void MathUtil::transformVector4(const float* matrix, const float* inVector, float* outVector)
{
    float x = inVector[0];
    float y = inVector[1];
    float z = inVector[2];
    float w = inVector[3];

    outVector[0] = x * matrix[0] + y * matrix[4] + z * matrix[8] + w * matrix[12];
    outVector[1] = x * matrix[1] + y * matrix[5] + z * matrix[9] + w * matrix[13];
    outVector[2] = x * matrix[2] + y * matrix[6] + z * matrix[10] + w * matrix[14];
    outVector[3] = x * matrix[3] + y * matrix[7] + z * matrix[11] + w * matrix[15];
}