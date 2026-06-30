// FUNC_NAME: cullAndTransformTriangles
undefined4 __fastcall cullAndTransformTriangles(ushort* pIndices, float* pMatrix, int vertexBase, int numTriangles, void* outputBuffer)
{
    // Global constants from the binary
    extern float g_scaleFactor;      // DAT_00e2b1a4
    extern float g_viewportMax;      // DAT_00e2cd54
    extern float g_viewportMin;      // DAT_00e44718

    int i;
    ushort* currentIndices;
    ushort* endIndices;
    undefined2* outputEntry;
    ushort triangleIndex;
    int counter;

    float fRow0[4], fRow1[4], fRow2[4], fRow3[4]; // matrix rows
    float fVar7, fVar8, fVar9, fVar10;
    float fVar11, fVar12, fVar13, fVar14;
    float fVar15, fVar16, fVar17, fVar18;
    float fVar26, fVar29, fVar30, fVar31;

    // Load matrix rows
    fVar11 = pMatrix[0]; fVar12 = pMatrix[1]; fVar13 = pMatrix[2]; fVar14 = pMatrix[3];
    fVar7 = pMatrix[4]; fVar8 = pMatrix[5]; fVar9 = pMatrix[6]; fVar10 = pMatrix[7];
    fVar15 = pMatrix[8]; fVar16 = pMatrix[9]; fVar17 = pMatrix[10]; fVar18 = pMatrix[11];
    fVar26 = pMatrix[12]; fVar29 = pMatrix[13]; fVar30 = pMatrix[14]; fVar31 = pMatrix[15];

    // Scaled translation components
    float fScaleX = g_scaleFactor * fVar26;
    float fScaleY = g_scaleFactor * fVar29;
    float fScaleZ = g_scaleFactor * fVar30;
    float fScaleW = g_scaleFactor * fVar31;

    // Second set (used for different vertices? Actually same scaled translation repeated)
    float fScaleX2 = g_scaleFactor * fVar26;
    float fScaleY2 = g_scaleFactor * fVar29;
    float fScaleZ2 = g_scaleFactor * fVar30;
    float fScaleW2 = g_scaleFactor * fVar31;

    // Third set
    float fScaleX3 = g_scaleFactor * fVar26;
    float fScaleY3 = g_scaleFactor * fVar29;
    float fScaleZ3 = g_scaleFactor * fVar30;
    float fScaleW3 = g_scaleFactor * fVar31;

    // Initialize output pointer
    // outputBuffer + 0x0c holds current count of written triangles (as short)
    // Then each entry is 16 bytes (8 shorts)
    short* pCount = (short*)((char*)outputBuffer + 0x0c);
    int entryCount = *pCount;
    outputEntry = (undefined2*)((char*)outputBuffer + (entryCount + 0x601) * 0x10); // Offset to next free slot

    // Loop over all triangles (each triangle has 3 indices)
    counter = 0;
    endIndices = pIndices + numTriangles * 3;
    for (currentIndices = pIndices; currentIndices < endIndices; currentIndices += 3)
    {
        // Vertices A, B, C
        ushort idxA = currentIndices[0];
        ushort idxB = currentIndices[1];
        ushort idxC = currentIndices[2];

        // Load vertex positions (stride 0x14 = 20 bytes)
        float* vertA = (float*)(vertexBase + idxA * 0x14);
        float ax = vertA[0], ay = vertA[1], az = vertA[2];
        float* vertB = (float*)(vertexBase + idxB * 0x14);
        float bx = vertB[0], by = vertB[1], bz = vertB[2];
        float* vertC = (float*)(vertexBase + idxC * 0x14);
        float cx = vertC[0], cy = vertC[1], cz = vertC[2];

        // Transform vertex A
        float txA = ax * fVar11 + ay * fVar7 + az * fVar15 + fScaleX;
        float tyA = ax * fVar12 + ay * fVar8 + az * fVar16 + fScaleY;
        float tzA = ax * fVar13 + ay * fVar9 + az * fVar17 + fScaleZ;
        float twA = ax * fVar14 + ay * fVar10 + az * fVar18 + fScaleW;

        // Transform vertex B
        float txB = bx * fVar11 + by * fVar7 + bz * fVar15 + fScaleX2;
        float tyB = bx * fVar12 + by * fVar8 + bz * fVar16 + fScaleY2;
        float tzB = bx * fVar13 + by * fVar9 + bz * fVar17 + fScaleZ2;
        float twB = bx * fVar14 + by * fVar10 + bz * fVar18 + fScaleW2;

        // Transform vertex C
        float txC = cx * fVar11 + cy * fVar7 + cz * fVar15 + fScaleX3;
        float tyC = cx * fVar12 + cy * fVar8 + cz * fVar16 + fScaleY3;
        float tzC = cx * fVar13 + cy * fVar9 + cz * fVar17 + fScaleZ3;
        float twC = cx * fVar14 + cy * fVar10 + cz * fVar18 + fScaleW3;

        // SIMD min/max operations for bounding box (using SSE intrinsics)
        __m128 vecA = _mm_set_ps(twA, tzA, tyA, txA);
        __m128 vecB = _mm_set_ps(twB, tzB, tyB, txB);
        __m128 vecC = _mm_set_ps(twC, tzC, tyC, txC);

        __m128 minVec = _mm_min_ps(vecA, vecB);
        minVec = _mm_min_ps(minVec, vecC);

        __m128 maxVec = _mm_max_ps(vecA, vecB);
        maxVec = _mm_max_ps(maxVec, vecC);

        // Extract X and Y min/max (only X and Y are checked)
        float minX = _mm_cvtss_f32(minVec);
        float minY = _mm_cvtss_f32(_mm_shuffle_ps(minVec, minVec, _MM_SHUFFLE(1,1,1,1)));
        float maxX = _mm_cvtss_f32(maxVec);
        float maxY = _mm_cvtss_f32(_mm_shuffle_ps(maxVec, maxVec, _MM_SHUFFLE(1,1,1,1)));

        // Check if the transformed triangle's bounding box is within the viewport bounds
        // (Only X and Y are checked; Z and W ignored)
        if ((minX <= g_viewportMax) && (maxX >= g_viewportMin) &&
            (minY <= g_viewportMax) && (maxY >= g_viewportMin))
        {
            // Triangle is visible; write output entry
            // Output structure: [unk1 (ushort), counter (ushort), ptrA (uint), ptrB (uint), ptrC (uint)]? Actually 8 shorts (16 bytes)
            // Based on writes: *puVar24 = uVar3; puVar24[1] = counter; *(uint*)(puVar24+2) = pointer to vertA; etc.
            // uVar3 = *(undefined2*)(param_5+8) — some index passed from caller
            ushort someIndex = *(ushort*)((char*)outputBuffer + 0x08);
            outputEntry[0] = someIndex;
            outputEntry[1] = (undefined2)counter;
            *(int*)(outputEntry + 2) = (int)vertA; // pointer to vertex A data
            *(int*)(outputEntry + 4) = (int)vertB;
            *(int*)(outputEntry + 6) = (int)vertC;
            outputEntry += 8; // advance by 16 bytes
        }

        counter++;
    }

    // Update the count in the output buffer
    int bytesWritten = (int)outputEntry - (int)((char*)outputBuffer + (entryCount + 0x601) * 0x10);
    *pCount = (short)(bytesWritten >> 4); // number of entries written (each 16 bytes)

    // Return success/failure? The original returned CONCAT31((int3)(uVar25 >> 8), (uVar25 & 0xfffffff0) != 0)
    // uVar25 = bytesWritten; so return 0 if even number of entries? Unclear, but likely a bool indicating if buffer overflow?
    return (bytesWritten & 0xfffffff0) != 0 ? 0x100 : 0; // simplified
}