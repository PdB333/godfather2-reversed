// FUNC_NAME: Math::rotateVectorByMatrix44
void Math::rotateVectorByMatrix44(float* outVec, const float* inVec, const float* matrix44)
{
    float x = inVec[0];
    float y = inVec[1];
    float z = inVec[2];

    // matrix44 is a 4x4 matrix (16 floats). The rotation part occupies:
    // indices 0,1,2 (first column/row), 4,5,6 (second), 8,9,10 (third).
    // This computes out = transpose(rotation) * in (if row-major) or rotation * in (if column-major).
    // Usually used to transform a direction vector from local to world or vice versa.
    outVec[0] = y * matrix44[4] + x * matrix44[0] + z * matrix44[8];
    outVec[1] = y * matrix44[5] + x * matrix44[1] + z * matrix44[9];
    outVec[2] = y * matrix44[6] + x * matrix44[2] + z * matrix44[10];
}