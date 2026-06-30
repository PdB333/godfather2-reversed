// FUNC_NAME: OcclusionTester::batchTestPoints
void __thiscall OcclusionTester::batchTestPoints(float* pointBuffer, uint8_t* outputFlags, int pointCount) {
    // Global constant (maybe 1.0f or a scaling factor)
    const float globalW = DAT_00e2b1a4;

    // Read zone enable flags from the object (offsets +0x60, +0x120, +0x1e0, +0x2a0, +0x360)
    uint8_t zoneFlags[5];
    zoneFlags[0] = *(uint8_t*)(this + 0x60);
    zoneFlags[1] = *(uint8_t*)(this + 0x120);
    zoneFlags[2] = *(uint8_t*)(this + 0x1e0);
    zoneFlags[3] = *(uint8_t*)(this + 0x2a0);
    zoneFlags[4] = *(uint8_t*)(this + 0x360);

    int outputIndex = 0;
    if (pointCount <= 0) return;

    // pointBuffer contains vectors of 4 floats (x, y, z, w) per point, 16 bytes each.
    // We start at +8 offset from the base pointer (to align with the loop pattern)
    float* currentPoint = pointBuffer + 2; // offset by 2 floats (8 bytes) for initial accesses

    do {
        float x = currentPoint[-2]; // point.x
        float y = currentPoint[-1]; // point.y
        float z = currentPoint[0];  // point.z
        float w = currentPoint[1];  // point.w

        uint32_t resultMask = 0;
        int zoneIndex = 0;

        // Plane data is stored at this+0x20 as an array of 5 zone plane sets, each 0x30 bytes apart.
        float* planeData = (float*)(this + 0x20);

        do {
            // For each zone, we have 8 plane tests (two groups of 4)
            // Group 1: four plane equations using coefficients stored at relative offsets
            float dot1 = planeData[-8] * x + planeData[-7] * y + planeData[-6] * z + planeData[-5] * globalW;
            float dot2 = planeData[-4] * x + planeData[-3] * y + planeData[-2] * z + planeData[-1] * globalW;
            float dot3 = planeData[4] * x + planeData[5] * y + planeData[6] * z + planeData[7] * globalW;
            float dot4 = planeData[0] * x + planeData[1] * y + planeData[2] * z + planeData[3] * globalW;

            // Compare w against each dot product, generate 4-bit mask (movmskps)
            uint32_t mask1 = 0;
            if (w >= dot1) mask1 |= 1;
            if (w >= dot2) mask1 |= 2;
            if (w >= dot3) mask1 |= 4;
            if (w >= dot4) mask1 |= 8;

            // Group 2: two additional plane tests using transformed coordinates
            float transformed1 = planeData[8] * y + planeData[9] * x + planeData[10] * z + planeData[11] * globalW;
            float transformed2 = planeData[12] * y + planeData[13] * x + planeData[14] * z + planeData[15] * globalW;
            // Two comparisons: w vs transformed1 and w vs transformed2 (replicated for SIMD)
            uint32_t mask2 = 0;
            if (w >= transformed1) mask2 |= 1;
            if (w >= transformed2) mask2 |= 2;

            // Combine masks: point is inside zone if all 8 tests pass?
            // The original code: uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX;
            // So if either mask2 or mask1 is non-zero? Actually it seems like the condition is "w < dot" -> outside.
            // The comparisons are set to 1 if w < dot, and then movmskps. So mask1 bits are 1 if point is outside that plane.
            // Then uVar11 = mask1, uVar10 = mask2.
            // Then (uVar10 | uVar11) -> if any outside, positive.
            // (0 < ...) - 1 -> becomes 0 if any outside, -1 (0xFFFFFFFF) if all inside.
            // Then & unaff_EBX (zone flag). So result is zone flag if fully inside, 0 otherwise.
            uint32_t combined = mask1 | mask2;
            uint8_t zoneContribution = (combined == 0) ? zoneFlags[zoneIndex] : 0;

            resultMask |= zoneContribution;

            zoneIndex++;
            planeData += 12; // 0x30 bytes = 12 floats
        } while (zoneIndex < 5);

        // Store result as a byte
        *(outputFlags + outputIndex) = (uint8_t)resultMask;

        outputIndex++;
        currentPoint += 4; // advance to next point (4 floats)
    } while (outputIndex < pointCount);
}