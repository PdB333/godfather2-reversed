// FUNC_NAME: Animated::computeBoundingBox (likely for 8 bone or child transforms)
void __thiscall Animated::computeBoundingBox(
    void *thisPtr,              // this (param_1) - class instance containing time & matrix array
    TRANSFORM_OUT *outVectors,  // param_2 - pointer to output transformed vertices (8 * 4 floats)
    float currentTime,          // param_3 - current time / blending factor
    float *outAABB              // param_4 - output AABB: outAABB[0..3] min, outAABB[4..7] max
)
{
    float *min;    // alias for outAABB
    float *max;    // outAABB + 4
    float *vertexPtr;   // points into outVectors (or local array)
    int matrixIndex;    // loop counter

    // —— Process 8 bone/sub-object transforms (each 16 bytes) ——
    // thisPtr + 0x50 -> array of 8 4x3 matrices (or 4x4?) 
    // Each iteration multiplies the current bone matrix by a predefined model vertex (stored in local array?)
    // and stores output into outVectors array (or a temporary local buffer).
    // The decompiler suggests the first result goes into local_90..local_84, and subsequent into local_80[0..27].
    // We model that as reading from a local vertex array that is filled by the callee.
    // For clarity, we treat outVectors as an 8-vector (4 floats each) buffer.
    // The callee "FUN_00aa2bb0" might be "multiplyVector4x4" taking (float *outVec, float *matrix)

    float *matrixPtr = (float *)((char *)thisPtr + 0x50); // +0x50: array of 8 transforms
    float *outVec = outVectors;  // assume outVectors holds 8 vectors of 4 floats each

    // First, transform all 8 vertices/bone endpoints:
    for (matrixIndex = 8; matrixIndex > 0; matrixIndex--, matrixPtr += 4) // assuming matrix is 4 floats? Actually 16 bytes per matrix? Use known offset +0x50 step 0x10 = 16 bytes
    {
        // matrixPtr points to current matrix (16 bytes, 4 floats)
        // outVec points to current output vector (4 floats)
        FUN_00aa2bb0(outVec, matrixPtr);  // transform vector by matrix
        outVec += 4; // advance to next output slot
    }

    // —— Initialize the AABB with the first transformed vertex ——
    // The decompiler captured the first vertex as local variables local_90, local_8c, etc.
    // But those likely come from outVectors[0]. We'll read from that array.
    float *firstVertex = outVectors;
    outAABB[0] = firstVertex[0];   // min X
    outAABB[1] = firstVertex[1];   // min Y
    outAABB[2] = firstVertex[2];   // min Z
    outAABB[3] = firstVertex[3];   // min W (used for time/scale?)
    outAABB[4] = firstVertex[0];   // max X
    outAABB[5] = firstVertex[1];   // max Y
    outAABB[6] = firstVertex[2];   // max Z
    outAABB[7] = firstVertex[3];   // max W

    // —— Sweep remaining 7 vertices to compute AABB ——
    // The decompiler loop uses local_80+2 as starting point, meaning it skips the first two floats of the second vertex?
    // Actually it processes the remaining vertices starting from index 2 of the array (local_80[2] = outVectors[1][0]? confusing)
    // To match the original math, we'll iterate over vertices 1..7 (8 vertices total, first already done).
    for (int vertexIdx = 1; vertexIdx < 8; vertexIdx++)
    {
        float *v = outVectors + vertexIdx * 4; // each vertex 4 floats

        // Minimise components
        if (v[0] < min[0]) min[0] = v[0];
        if (v[1] < min[1]) min[1] = v[1];
        if (v[2] < min[2]) min[2] = v[2];
        if (v[3] < min[3]) min[3] = v[3];

        // Maximise components
        if (v[0] > max[0]) max[0] = v[0];
        if (v[1] > max[1]) max[1] = v[1];
        if (v[2] > max[2]) max[2] = v[2];
        if (v[3] > max[3]) max[3] = v[3];
    }

    // —— Adjust AABB based on time difference ——
    float storedTime = *(float *)((char *)thisPtr + 0x3c); // +0x3c: stored time/offset
    if (currentTime != storedTime)
    {
        float delta = currentTime - storedTime;

        // Expand min by subtracting delta (moving backward)
        min[0] -= delta;
        min[1] -= delta;
        min[2] -= delta;
        // min[3] untouched (w component)

        // Expand max by adding delta (moving forward)
        max[0] += delta;
        max[1] += delta;
        max[2] += delta;
        // max[3] untouched
    }

    return;
}