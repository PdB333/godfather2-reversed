// FUNC_NAME: TriangleCuller::cullTriangles
undefined4 __fastcall TriangleCuller::cullTriangles(ushort* indexBuffer, float* worldViewProj, int vertexBuffer, int triangleCount, void* clipOutput)
{
    ushort* puVar1;
    float* pfVar2;
    undefined2 uVar3;
    ushort index0, index1, index2;
    float vertex0x, vertex0y, vertex0z, vertex0w; // actually we only have x,y,z from vertex
    float v0x, v0y, v0z;
    float v1x, v1y, v1z;
    float v2x, v2y, v2z;
    float fVar7, fVar8, fVar9, fVar10; // matrix row1? Actually first row?
    float fVar11, fVar12, fVar13, fVar14; // row0?
    float fVar15, fVar16, fVar17, fVar18; // row2?
    float fVar19, fVar20, fVar21; // temp vertex components
    float fVar34, fVar36, fVar38, fVar40; // transformed second vertex
    float fVar41, fVar43, fVar44, fVar45; // scaled translation row?
    float fVar26, fVar29, fVar30, fVar31; // matrix row3 (translation)
    float fVar33, fVar35, fVar37, fVar39; // scaled translation (applied to first vertex)
    float clipMinX, clipMinY, clipMaxX, clipMaxY;
    float transformed1[4], transformed2[4], transformed3[4];
    float minVec[4], maxVec[4], tempVec[4];
    short triangleIndex = 0;
    undefined2* puVar24;

    // Constants for clip space bounds (likely -1 to 1 in NDC)
    float clipFar = DAT_00e2cd54;    // e.g., 1.0
    float clipNear = DAT_00e44718;   // e.g., -1.0

    // Extract translation (row 3) and scale by some conversion factor
    fVar26 = worldViewProj[0xc] * DAT_00e2b1a4;
    fVar29 = worldViewProj[0xd] * DAT_00e2b1a4;
    fVar30 = worldViewProj[0xe] * DAT_00e2b1a4;
    fVar31 = worldViewProj[0xf] * DAT_00e2b1a4;
    fVar33 = fVar26;
    fVar35 = fVar29;
    fVar37 = fVar30;
    fVar39 = fVar31;
    fVar41 = fVar26;
    fVar43 = fVar29;
    fVar44 = fVar30;
    fVar45 = fVar31;

    // First row of matrix (scale/rotate)
    fVar11 = *worldViewProj;          // m00
    fVar12 = worldViewProj[1];        // m01
    fVar13 = worldViewProj[2];        // m02
    fVar14 = worldViewProj[3];        // m03
    // Second row
    fVar7 = worldViewProj[4];         // m10
    fVar8 = worldViewProj[5];         // m11
    fVar9 = worldViewProj[6];         // m12
    fVar10 = worldViewProj[7];        // m13
    // Third row
    fVar15 = worldViewProj[8];        // m20
    fVar16 = worldViewProj[9];        // m21
    fVar17 = worldViewProj[10];       // m22
    fVar18 = worldViewProj[11];       // m23

    // Compute base pointer to clip entry buffer (offset 0x6010)
    // clipOutput structure: +0x8 = materialID, +0xC = nextIndex (count of stored entries)
    undefined2* clipEntryBuffer = (undefined2*)((*(ushort*)((byte*)clipOutput + 0xC) + 0x601) * 0x10 + (int)clipOutput);
    uVar3 = *(undefined2*)((byte*)clipOutput + 8);  // materialID

    puVar1 = indexBuffer + triangleCount * 3; // end pointer
    puVar24 = clipEntryBuffer;

    do {
        index0 = *indexBuffer;
        pfVar2 = (float*)(vertexBuffer + (uint)index0 * 0x14);
        v0x = *pfVar2;
        v0y = pfVar2[1];
        v0z = pfVar2[2];
        index1 = indexBuffer[1];
        // Transform first vertex
        transformed1[0] = v0x * fVar11 + v0y * fVar7 + v0z * fVar15 + fVar33;
        transformed1[1] = v0x * fVar12 + v0y * fVar8 + v0z * fVar16 + fVar35;
        transformed1[2] = v0x * fVar13 + v0y * fVar9 + v0z * fVar17 + fVar37;
        transformed1[3] = v0x * fVar14 + v0y * fVar10 + v0z * fVar18 + fVar39;

        pfVar2 = (float*)(vertexBuffer + (uint)index1 * 0x14);
        v1x = *pfVar2;
        v1y = pfVar2[1];
        v1z = pfVar2[2];
        index2 = indexBuffer[2];
        // Transform second vertex
        fVar34 = v1x * fVar11 + v1y * fVar7 + v1z * fVar15 + fVar41;
        fVar36 = v1x * fVar12 + v1y * fVar8 + v1z * fVar16 + fVar43;
        fVar38 = v1x * fVar13 + v1y * fVar9 + v1z * fVar17 + fVar44;
        fVar40 = v1x * fVar14 + v1y * fVar10 + v1z * fVar18 + fVar45;

        pfVar2 = (float*)(vertexBuffer + (uint)index2 * 0x14);
        v2x = *pfVar2;
        v2y = pfVar2[1];
        v2z = pfVar2[2];
        // Transform third vertex
        transformed3[0] = v2x * fVar11 + v2y * fVar7 + v2z * fVar15 + fVar26;
        transformed3[1] = v2x * fVar12 + v2y * fVar8 + v2z * fVar16 + fVar29;
        transformed3[2] = v2x * fVar13 + v2y * fVar9 + v2z * fVar17 + fVar30;
        transformed3[3] = v2x * fVar14 + v2y * fVar10 + v2z * fVar18 + fVar31;

        // Compute bounding box min/max for the three vertices in clip space
        // Using SSE minps/maxps equivalent
        tempVec[0] = fVar34; tempVec[1] = fVar36; tempVec[2] = fVar38; tempVec[3] = fVar40;
        // min of first and second vertex
        minVec[0] = min(transformed1[0], tempVec[0]);
        minVec[1] = min(transformed1[1], tempVec[1]);
        minVec[2] = min(transformed1[2], tempVec[2]);
        minVec[3] = min(transformed1[3], tempVec[3]);
        maxVec[0] = max(transformed1[0], tempVec[0]);
        maxVec[1] = max(transformed1[1], tempVec[1]);
        maxVec[2] = max(transformed1[2], tempVec[2]);
        maxVec[3] = max(transformed1[3], tempVec[3]);
        // Then min of (minVec, third vertex)
        minVec[0] = min(minVec[0], transformed3[0]);
        minVec[1] = min(minVec[1], transformed3[1]);
        minVec[2] = min(minVec[2], transformed3[2]);
        minVec[3] = min(minVec[3], transformed3[3]);
        maxVec[0] = max(maxVec[0], transformed3[0]);
        maxVec[1] = max(maxVec[1], transformed3[1]);
        maxVec[2] = max(maxVec[2], transformed3[2]);
        maxVec[3] = max(maxVec[3], transformed3[3]);

        // Check if bounding box overlaps visible clip region (x and y only, likely z is also checked but code only uses x,y? Actually it checks x and y: minX <= clipFar && clipNear <= maxX and similarly for y)
        clipMinX = minVec[0];
        clipMinY = minVec[1];
        clipMaxX = maxVec[0];
        clipMaxY = maxVec[1];
        if (((clipMinX <= clipFar) && (clipNear <= clipMaxX)) &&
            ((clipMinY <= clipFar) && (clipNear <= clipMaxY))) 
        {
            // Triangle visible, write clip entry
            *puVar24 = uVar3;                      // materialID
            puVar24[1] = (undefined2)triangleIndex; // triangle index in batch
            *(uint*)(puVar24 + 2) = vertexBuffer + (uint)index0 * 0x14; // vertex0 pointer
            *(uint*)(puVar24 + 4) = vertexBuffer + (uint)index1 * 0x14; // vertex1 pointer
            *(uint*)(puVar24 + 6) = vertexBuffer + (uint)index2 * 0x14; // vertex2 pointer
            puVar24 += 8; // advance to next entry (8 undefined2 = 16 bytes)
        }
        triangleIndex++;
        indexBuffer += 3;
    } while ((indexBuffer != puVar1) && ((uint)((-0x6010 - (int)clipOutput) + (int)puVar24 >> 4) < 0x1000));

    // Update next index in clip output
    *(short*)((byte*)clipOutput + 0xC) = (short)(((int)puVar24 + (-0x6010 - (int)clipOutput)) >> 4);
    // Return number of bytes written as part of a packed value? Actually original returns something odd: CONCAT31((int3)(uVar25 >> 8), (uVar25 & 0xfffffff0) != 0). We'll just return count of entries written.
    uint bytesWritten = (int)puVar24 - (int)clipEntryBuffer;
    // The original returns: high 3 bytes = bytesWritten >> 8, low byte = (bytesWritten & 0xfffffff0) != 0
    return (bytesWritten >> 8) | ((bytesWritten & 0xfffffff0) != 0);
}