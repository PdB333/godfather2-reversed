// FUN_0041ceb0: Matrix44::createFromTwoVectors
void Matrix44::createFromTwoVectors(const float* param_1, const float* param_2)
{
    float* puVar4 = (float*)allocateMemory(0xd, 4, 0, 1, 0); // allocateMemory(count=13, size=4, flags, alignment, ...)
    if (puVar4 != nullptr) {
        // Build a 4x4 matrix from two 4-element vectors.
        // The specific pattern creates a matrix with repeated values,
        // likely used for a bilinear or skew transformation.

        // Row 0
        puVar4[0] = param_1[0];
        puVar4[1] = param_1[1];
        puVar4[2] = param_2[0];
        puVar4[3] = param_2[1];

        // Row 1
        puVar4[4] = param_1[2];
        puVar4[5] = param_1[1];
        puVar4[6] = param_2[2];
        puVar4[7] = param_2[1];

        // Row 2
        puVar4[8] = param_1[2];
        puVar4[9] = param_1[3];
        puVar4[10] = param_2[2];
        puVar4[11] = param_2[3];

        // Row 3
        puVar4[12] = param_1[0];
        puVar4[13] = param_1[3];
        puVar4[14] = param_2[0];
        puVar4[15] = param_2[3];

        postAllocation(); // post-allocation callback
    }
}