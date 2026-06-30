// FUNC_NAME: Vec4::createMatrixFromThis
void __thiscall Vec4::createMatrixFromThis()
{
    float *newMatrix; // pointer to allocated 4x4 matrix
    float *src = (float *)this; // this is Vec4 with 4 floats

    // Allocate a 4x4 matrix (16 floats) using custom allocator
    newMatrix = (float *)allocate(0xd, 4, 0, 1, 0); // parameters: size class? count? alignment?
    if (newMatrix != nullptr)
    {
        float v0 = src[0]; // x
        float v1 = src[1]; // y
        float v2 = src[2]; // z
        float v3 = src[3]; // w
        float globalConst = *reinterpret_cast<float*>(0x00e2b1a4); // possibly 1.0f or 0.5f

        // Build matrix from the four vector components
        newMatrix[0] = v0;          // (0,0)
        newMatrix[1] = v1;          // (0,1)
        newMatrix[2] = 0.0f;        // (0,2)
        newMatrix[3] = 0.0f;        // (0,3)
        newMatrix[4] = v2;          // (1,0)
        newMatrix[5] = v1;          // (1,1)
        newMatrix[6] = globalConst; // (1,2)
        newMatrix[7] = 0.0f;        // (1,3)
        newMatrix[8] = v2;          // (2,0)
        newMatrix[9] = v3;          // (2,1)
        newMatrix[10] = globalConst;// (2,2)
        newMatrix[11] = globalConst;// (2,3)
        newMatrix[12] = v0;         // (3,0)
        newMatrix[13] = v3;         // (3,1)
        newMatrix[14] = 0.0f;       // (3,2)
        newMatrix[15] = globalConst;// (3,3)

        // Post-initialization callback (e.g., set identity or finalize)
        finalizeCreation();
    }
    // Memory leak? Possibly the caller manages lifetime.
}