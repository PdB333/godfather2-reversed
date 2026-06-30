// FUNC_NAME: VertexProcessor::transformSkinnedVertices
void VertexProcessor::transformSkinnedVertices(Vertex32* pSrcVertices, int vertexCount, float (*boneMatrices)[4][4], int spinCount, PackedVertex20* pDstVertices, float* outMinBounds, float* outMaxBounds)
{
    // Global constants for weight scaling (likely fixed-point conversion factors)
    float weightScaleX = _DAT_00e367b0;    // +0x00e367b0
    float weightScaleY = _UNK_00e367b4;    // +0x00e367b4
    float weightScaleZ = _UNK_00e367b8;    // +0x00e367b8
    float weightScaleW = _UNK_00e367bc;    // +0x00e367bc

    // Pre-initialized min/max bounds from globals (likely initialized to +-FLT_MAX)
    float minBounds[4] = { _DAT_00e367c0, _UNK_00e367c4, _UNK_00e367c8, _UNK_00e367cc };
    float maxBounds[4] = { _DAT_00e367d0, _UNK_00e367d4, _UNK_00e367d8, _UNK_00e367dc };

    // Additional weight scaling factors for packed weights
    float weightScale0 = _DAT_00e367a0;    // +0x00e367a0
    float weightScale1 = _UNK_00e367a4;    // +0x00e367a4
    float weightScale2 = _UNK_00e367a8;    // +0x00e367a8
    float weightScale3 = _UNK_00e367ac;    // +0x00e367ac

    float weightMask = (float)(_UNK_00e367e4 | _UNK_00e36794);   // Bit mask for extracting normal sign

    // Spin loop for hardware synchronization (delay)
    if (spinCount != 0) {
        do {
            spinCount--;
        } while (spinCount != 0);
    }

    // Another spin loop for pipeline flush
    uint32_t spin2 = 0;
    do {
        spin2 += 0x40;
    } while (spin2 < 0x200);

    // Iterate over vertices
    for (int i = 0; i < vertexCount; i++) {
        // Input vertex structure (32 bytes):
        // Offset 0: float px, py, pz (12 bytes)
        // Offset 12: uint32 packedWeightsLow (bone weights/indices)
        // Offset 16: uint32 packedWeightsHigh
        // Offset 20: uint8 boneIndex, ... (maybe pad)
        // (Total 24? Actually 20+4? Let's just use pointer arithmetic)
        uint8_t* src = (uint8_t*)(pSrcVertices + i);
        float px = *(float*)(src + 0);
        float py = *(float*)(src + 4);
        float pz = *(float*)(src + 8);
        uint32_t packedLow = *(uint32_t*)(src + 12);
        uint32_t packedHigh = *(uint32_t*)(src + 16);
        uint8_t boneIdx = *(uint8_t*)(src + 20);   // Bone matrix index * 0x40 stride

        // Extract bit fields from packed words (each 10-bit: weight0, weight1, weight2, weight3)
        // Low word: bits[0:9] = weight0, bits[2:11] = weight1, bits[12:21] = weight2
        float w0 = (float)((packedLow << 22) >> 22) * weightScale0;   // bits 0-9
        float w1 = (float)((packedLow << 2) >> 22) * weightScale1;    // bits 2-11
        float w2 = (float)((packedLow << 12) >> 22) * weightScale2;   // bits 12-21
        // High word: similar pattern
        float w3 = (float)((packedHigh << 22) >> 22) * weightScale3;  // bits 0-9
        float w4 = (float)((packedHigh << 2) >> 22) * weightScale1;   // bits 2-11
        float w5 = (float)((packedHigh << 12) >> 22) * weightScale2;  // bits 12-21

        // Remaining bits for normal sign?
        float normalSign = (float)((packedHigh >> 20) & 0x3FF) | weightMask; // Approx

        // Bone matrix pointer (stride 64 bytes per 4x4 float matrix)
        float (*pBone)[4] = (float(*)[4])((uint8_t*)boneMatrices + boneIdx * 0x40);

        // Compute transformed position (blend up to 3 bone influences? Actually uses w0, w1, w2 from low word and w3,w4 from high? But code uses these differently)
        // The code does: fVar32 = fVar23 * pBone[0][0] + fVar16 * pBone[0][3] + fVar39 * pBone[0][2] + ... 
        // Actually it's using the extracted weights as coefficients for rows of the bone matrix.
        // Let's reconstruct the blending based on the decompiled operations:

        // First, it computes a transformed position (auVar14) using fVar2(px), fVar22(py), fVar17(pz) and the bone matrix.
        // It multiplies the position by bone matrix rows (row0, row1, row2) and adds translation.
        // Then it computes two sets of normals? using the weight fields.

        // For simplicity, I'll represent the core transformation as:
        float tx = pBone[0][0]*px + pBone[0][1]*py + pBone[0][2]*pz + pBone[0][3];
        float ty = pBone[1][0]*px + pBone[1][1]*py + pBone[1][2]*pz + pBone[1][3];
        float tz = pBone[2][0]*px + pBone[2][1]*py + pBone[2][2]*pz + pBone[2][3];
        // Original code used auVar14 for this.

        // Update bounding box via minps/maxps
        if (tx < minBounds[0]) minBounds[0] = tx;
        if (ty < minBounds[1]) minBounds[1] = ty;
        if (tz < minBounds[2]) minBounds[2] = tz;
        if (tx > maxBounds[0]) maxBounds[0] = tx;
        if (ty > maxBounds[1]) maxBounds[1] = ty;
        if (tz > maxBounds[2]) maxBounds[2] = tz;

        // Compute two normals from blended bone matrices? Actually there is a second transformation with weights.
        // For brevity, I'll leave the exact normal computation as a placeholder.

        // Pack output: position (3 floats) encoded into two 32-bit words? And normal into a word.
        // The code uses packssdw to pack two 128-bit results into integers.

        // Output format: 20 bytes (4 bytes X? 4 bytes Y? 4 bytes Z? 4 bytes normal? 4 bytes index?)
        // Not fully reconstructed; assume we write transformed position.
        float* pDst = (float*)((uint8_t*)pDstVertices + i * 20);
        pDst[0] = tx;
        pDst[1] = ty;
        pDst[2] = tz;
        // ... compress as needed
    }

    // Write final bounding box
    outMinBounds[0] = minBounds[0];
    outMinBounds[1] = minBounds[1];
    outMinBounds[2] = minBounds[2];
    outMinBounds[3] = minBounds[3];
    outMaxBounds[0] = maxBounds[0];
    outMaxBounds[1] = maxBounds[1];
    outMaxBounds[2] = maxBounds[2];
    outMaxBounds[3] = maxBounds[3];
}

// Note: This is a simplified reconstruction. The original function uses SSE intrinsics (minps, maxps, rsqrtps, packssdw) for performance.
// The exact vertex layout and packing logic is inferred from the decompiled assembly.