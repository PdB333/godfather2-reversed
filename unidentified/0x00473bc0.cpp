// FUN_00473bc0: MathUtils::computeDirectionTransformFromPoints
void MathUtils::computeDirectionTransformFromPoints(const float* pointA, const float* pointB, float* outLength, 
                                                    float* outMatrix0, float* outMatrix1, float* outMatrix2)
{
    // Compute direction vector from pointA to pointB
    float dx = pointB[0] - pointA[0];
    float dy = pointB[1] - pointA[1];
    float dz = pointB[2] - pointA[2];

    // Squared length
    float lenSq = dx * dx + dy * dy + dz * dz;
    float length;
    float scale;

    // Epsilon threshold (DAT_00e2cbe0)
    if (lenSq <= 0.0000000000000000000000000000000000000117549435) // placeholder; actual value unknown
    {
        length = 0.0f;
        scale = 0.0f;
    }
    else
    {
        length = sqrtf(lenSq);
        scale = 1.0f / length;  // DAT_00e2b1a4 is likely 1.0
    }

    // Normalize direction vector
    float dirX = dx * scale;
    float dirY = dy * scale;
    float dirZ = dz * scale;

    // Output length if desired
    if (outLength != nullptr)
    {
        *outLength = length;
    }

    // Compute rotation from reference vector (DAT_00e32ac0) to direction
    // FUN_0056c6b0 likely constructs a rotation (matrix/quaternion) that rotates the reference vector to dir
    // Output stored in a 76-byte buffer (local_50) — possibly a 4x4 float matrix (16*4=64) or quaternion+scale?
    // The 76 bytes could be a 3x4 matrix (12*4=48) plus extra? Unclear.
    float transformBuffer[19]; // 76 bytes / 4 = 19 floats
    MathUtils::rotationFromVectorToVector(&dirX, &s_referenceVector, transformBuffer);
    // FUN_0056c180 likely writes the transform into three output matrix rows (each 4 floats? or 3x4?)
    // outMatrix0, outMatrix1, outMatrix2 are likely pointers to 4-element float arrays (the rows of a 3x4 matrix)
    MathUtils::setTransformFromBuffer(transformBuffer, outMatrix0, outMatrix1, outMatrix2);
}