// FUNC_NAME: BuildCustomTransformMatrix
void BuildCustomTransformMatrix(float param1, float param2, float param3, float param4,
                                float* outMatrix1, float* outMatrix2)
{
    // Constants from global data
    static const float kScaleFactor = *(float*)0x00e2cd54;  // some scaling factor
    static const float kConstantA = *(float*)0x00e2b1a4;    // e.g., 1.0
    static const float kConstantB = *(float*)0x00e44564;    // e.g., 1.0 (maybe pi/180?)
    // Tables for interpolation
    static float g_tableA[/*size?*/] = { /* at 0x011f6bb8 */ };
    static float g_tableB[/*size?*/] = { /* at 0x011f6bbc */ };
    static int   g_indexTable[/*size?*/] = { /* at 0x011f6be8 */ };

    // Thread-local storage dereference to get some index
    int* fsBase = (int*)__readfsdword(0x2c);
    int* somePtr = *(int**)(fsBase); // double indirection
    int useIndex = (somePtr[0x0D] != 0) ? 1 : 0;

    // Apply scaling factor
    float scaledParam1 = param1 * kScaleFactor;

    // Call math functions (likely trigonometric, e.g., sin/cos)
    double dVar4 = (double)scaledParam1;
    extern void MATH_SinCos1(double);  // placeholder
    MATH_SinCos1();  // side effect might set global state
    double dVar5 = (double)scaledParam1;
    extern void MATH_SinCos2(double);  // placeholder
    MATH_SinCos2();

    float fVar1 = kConstantA;
    float fVar3 = 0.0f;
    float fVar6 = kConstantA;

    // Lookup from tables using index
    int tableIdx = g_indexTable[useIndex];
    if (tableIdx != -1) {
        fVar3 = g_tableA[tableIdx * 3];
        fVar6 = g_tableB[tableIdx * 3];
    }

    // Compute intermediate values
    float fVar6New = (fVar6 * param4 - fVar3 * param3) * (kConstantA / (param4 - param3));
    float fVar7 = kConstantB - (float)(dVar4 / dVar5);

    // Fill outMatrix1 (16 floats, interpreted as 4x4 row-major matrix)
    outMatrix1[10] = fVar6New;   // row2, col2
    outMatrix1[0]  = fVar7;      // row0, col0
    outMatrix1[1]  = 0.0f;      // row0, col1
    outMatrix1[2]  = 0.0f;      // row0, col2
    outMatrix1[3]  = 0.0f;      // row0, col3
    outMatrix1[4]  = 0.0f;      // row1, col0
    outMatrix1[5]  = ((float)dVar4 / (float)dVar5) * param2; // row1, col1
    outMatrix1[6]  = 0.0f;      // row1, col2
    outMatrix1[7]  = 0.0f;      // row1, col3
    outMatrix1[8]  = 0.0f;      // row2, col0
    outMatrix1[9]  = 0.0f;      // row2, col1
    outMatrix1[11] = fVar1;     // row2, col3
    outMatrix1[12] = 0.0f;      // row3, col0
    outMatrix1[13] = 0.0f;      // row3, col1
    outMatrix1[14] = fVar3 * param3 - fVar6New * param3; // row3, col2
    outMatrix1[15] = 0.0f;      // row3, col3

    // Optionally fill outMatrix2 as a derivative matrix
    if (outMatrix2 != nullptr) {
        outMatrix2[1] = 0.0f;
        outMatrix2[2] = 0.0f;
        outMatrix2[3] = 0.0f;
        outMatrix2[4] = 0.0f;
        outMatrix2[0] = fVar1 / fVar7;
        outMatrix2[5] = fVar1 / outMatrix1[5];
        outMatrix2[6] = 0.0f;
        outMatrix2[7] = 0.0f;
        outMatrix2[8] = 0.0f;
        outMatrix2[9] = 0.0f;
        outMatrix2[10] = 0.0f;
        float denom = outMatrix1[14];
        outMatrix2[12] = 0.0f;
        outMatrix2[13] = 0.0f;
        outMatrix2[11] = fVar1 / denom;
        outMatrix2[14] = fVar1;
        outMatrix2[15] = kConstantB - outMatrix1[10] / denom;
    }
}