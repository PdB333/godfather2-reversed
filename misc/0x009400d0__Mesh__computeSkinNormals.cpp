// FUNC_NAME: Mesh::computeSkinNormals
void __thiscall Mesh::computeSkinNormals(float *outBuffer, float *inBuffer) {
    // outBuffer: output float array (8 + 4*numTriangles floats)
    // inBuffer: input float array (bone-weighted vertex positions? includes position and maybe normal at +28? )
    // Table at 0x00d8b278: triangle vertex index triplets (A, B, C) for normal computation
    static const int normalIndices[] = {
        0, 1, 2,  // vertex indices: A, B, C (note: order may matter)
        1, 2, 3,
        2, 3, 0
    }; // 3 triangles, each with 3 indices, stored as [A, B, C] per triangle
    // Actually the loop uses piVar8[-1], piVar8[0], piVar8[1] as indices into inBuffer
    // Each triplet: indexA, indexB, indexC (where C is the vertex whose normal is computed from triangle ABC)
    // The loop writes normals at outBuffer[0x20 + t*4] for each triangle t (stored as 4 floats: normal xyz, then something)

    float *normalOut = outBuffer + 11; // +0x2C? Actually param_1 + 0xb = float offset 11 (44 bytes), start of normal storage
    const int *triPtr = normalIndices;
    const int *triEnd = triPtr + sizeof(normalIndices) / sizeof(int);

    while (triPtr < triEnd) {
        int idxA = triPtr[-1];
        int idxB = triPtr[0];
        int idxC = triPtr[1];
        float *vertexC = inBuffer + idxC * 4; // vertex C (the vertex whose normal we compute)

        // Edge vectors: AB = B - A, AC = C - A? Actually from code: fVar10 = inBuffer[idxA*4] - inBuffer[idxB*4] => vector BA? Let's keep consistent with code.
        // Code computes: fVar10 = inBuffer[idxA*4] - inBuffer[idxB*4] -> B->A
        // fVar11 = vertexC - inBuffer[idxB*4] -> B->C
        // So normal = cross(BA, BC)
        float bx = inBuffer[idxB * 4];
        float by = inBuffer[idxB * 4 + 1];
        float bz = inBuffer[idxB * 4 + 2];

        float ax = inBuffer[idxA * 4];
        float ay = inBuffer[idxA * 4 + 1];
        float az = inBuffer[idxA * 4 + 2];

        float cx = vertexC[0];
        float cy = vertexC[1];
        float cz = vertexC[2];

        float v1x = ax - bx; // BA
        float v1y = ay - by;
        float v1z = az - bz;

        float v2x = cx - bx; // BC
        float v2y = cy - by;
        float v2z = cz - bz;

        // Cross product
        float nx = v1y * v2z - v1z * v2y;
        float ny = v1z * v2x - v1x * v2z;
        float nz = v1x * v2y - v1y * v2x;

        // Store normal (x,y,z) and a dummy value (original *pfVar9 was saved then overwritten with the cross product's w? Actually the code sets *pfVar9 to a redundant expression then restores fVar6, which is the old value. So it's a no-op. We just store the normal as 3 components and leave the fourth unchanged.)
        normalOut[-3] = nx;
        normalOut[-2] = ny;
        normalOut[-1] = nz;
        // *normalOut remains unchanged (the w component is preserved from the previous triangle or uninitialized)
        // But the code writes zero then restores; we can just not touch it.

        triPtr += 3;
        normalOut += 4; // advance to next triangle's normal slot
    }

    // Copy first 4 floats from input to output (likely position)
    outBuffer[0] = inBuffer[0];
    outBuffer[1] = inBuffer[1];
    outBuffer[2] = inBuffer[2];
    outBuffer[3] = inBuffer[3];
    // Copy next 4 floats from input offset 0x1c (28) to output offset 4 (16)
    outBuffer[4] = inBuffer[28];
    outBuffer[5] = inBuffer[29];
    outBuffer[6] = inBuffer[30];
    outBuffer[7] = inBuffer[31];
}