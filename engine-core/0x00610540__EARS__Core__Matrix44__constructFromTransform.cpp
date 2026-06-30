// FUNC_NAME: EARS::Core::Matrix44::constructFromTransform
void Matrix44::constructFromTransform(void)
{
    // allocate memory for new matrix (size: 13 * 4 bytes? but we use 16 fields)
    float *newMatrix = (float *)allocateMemory(0xd, 4, 0, 1, 0); // FUN_0060cd00
    if (newMatrix != (float *)0x0) {
        float src0 = this->field0;      // unaff_ESI[0]
        float src1 = this->field1;      // unaff_ESI[1]
        float src2 = this->field2;      // unaff_ESI[2]
        float src3 = this->field3;      // unaff_ESI[3]
        float globalConst = *(float *)0x00e2b1a4; // DAT_00e2b1a4, possibly 1.0f or 0.0f

        newMatrix[0] = src0;
        newMatrix[1] = src1;
        newMatrix[2] = 0.0f;
        newMatrix[3] = 0.0f;
        newMatrix[4] = src2;
        newMatrix[5] = src1;
        newMatrix[6] = globalConst;
        newMatrix[7] = 0.0f;
        newMatrix[8] = src2;
        newMatrix[9] = src3;
        newMatrix[10] = globalConst;
        newMatrix[11] = globalConst;
        newMatrix[12] = src0;
        newMatrix[13] = src3;
        newMatrix[14] = 0.0f;
        newMatrix[15] = globalConst;

        // post-initialization step (e.g., normalize or multiply)
        initMatrix(); // FUN_0060cde0
    }
    return;
}