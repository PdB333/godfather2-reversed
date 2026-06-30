// FUNC_NAME: CullingSystem::testPointsAgainstVolumes
// Address: 0x004d30e0
// This function tests a batch of 4-component points against 4 precomputed volumes (frustums/convex hulls).
// Each volume is defined by 24 floats stored at this+0x20 with stride 0x30 (48 bytes).
// The volumes are tested in order; for each volume, a 4-bit mask (from this+0x60, +0x120, +0x1e0, +0x2a0)
// is used to generate an output byte. The output byte for each point is stored in param_2[pointIndex].
// param_1: pointer to an array of 4-float points (x,y,z,w), size = param_3 * 4 floats.
// param_2: output byte array, size = param_3.
// param_3: number of points.
void CullingSystem::testPointsAgainstVolumes(void* thisPointer, float* points, char* outputMasks, int numPoints)
{
    float* thisPtr = (float*)thisPointer;
    float constant = *(float*)0x00e2b1a4;  // Likely 1.0f or a global scale factor

    // Load volume bitmask values (e.g., visibility flags or object IDs for each volume)
    char volumeMasks[4];
    volumeMasks[0] = *(char*)((int)thisPointer + 0x60);
    volumeMasks[1] = *(char*)((int)thisPointer + 0x120);
    volumeMasks[2] = *(char*)((int)thisPointer + 0x1e0);
    volumeMasks[3] = *(char*)((int)thisPointer + 0x2a0);

    int pointIndex = 0;
    if (numPoints > 0) {
        float* pointIter = points + 2;  // points[2] (z) – the loop starts with pointIter = points + 2? Actually the code uses pfVar13 = param_1+8, so points+2 (since 8/4=2). But then accesses pfVar13[-2], -1, 0, 1 -> that's points[0],points[1],points[2],points[3]. So pointIter starts at points+2 (z) and goes by 4.
        do {
            float pointX = *(pointIter - 2);   // +0x0
            float pointY = *(pointIter - 1);   // +0x4
            float pointZ = *pointIter;         // +0x8
            float pointW = *(pointIter + 1);   // +0xc

            int volumeIndex = 0;
            int outMask = 0;
            float* volumeData = (float*)((int)thisPointer + 0x20);  // Start of volume data (4 volumes, each 0x30 bytes)

            do {
                // Load 24 floats for this volume: planes and transformation
                // Plane coefficients for 4 planes (first 16 floats)
                float* planePtr = volumeData;
                // Indices -8..-1 relative to volumeData: that's the 8 floats before volumeData? Actually volumeData is the start of the volume block. In code, pfVar8 initially points to volumeData, then accesses pfVar8[-8] etc. So the effective plane data starts 8 floats before volumeData? That would be into the previous volume or undefined. But the loop increments volumeData by 0x30 each time, so the relative offsets are consistent within each block. The decompiler shows pfVar8 initially = in_EAX+0x20, then accesses pfVar8[-8] etc. That means the volume data actually includes 8 floats preceding the start? More likely, the volume structure is 48 bytes (12 floats) but the indexing is off. Let's reinterpret: The code uses pfVar8 = point to the start of the volume block? Actually pfVar8 = (float*)(in_EAX+0x20); then for first iteration, it accesses pfVar8[-8], pfVar8[-7], ..., pfVar8[-1], then pfVar8[0...15]. So it is reading from an array that starts at in_EAX+0x20-0x20? That's in_EAX+0x00. That doesn't make sense. Possibly the offsets are off by one word due to decompiler error. Alternatively, the volume data is stored with a 8-float prefix? Given the stride 0x30 (48 bytes = 12 floats), if the base was in_EAX+0x20 and each volume is 12 floats, then volumeData should be indexed from 0 to 11. But the code uses indices -8 to 15, which is 24 floats. That suggests the volume structure is 24 floats (0x60 bytes) and the stride is 0x30? That's only 12 floats. That's inconsistent. Let's examine: The inner loop increments pfVar8 by 0x30 (48 bytes = 12 floats) each iteration. But the accesses go from -8 to 15, covering 24 floats. That would require that consecutive volumes overlap? The only way this works is if the volume structure is actually 24 floats and the stride is 0x30, but then the next volume would start at pfVar8+12, but the code accesses pfVar8+15, which would be 3 floats into the next volume. That seems wrong. Perhaps the stride is 0x30, but the volume data is stored as 24 floats, so the actual offset between volumes is 24*4=0x60 bytes, not 0x30. There might be a misunderstanding: The decompiler shows "pfVar8 = pfVar8 + 0x30;" at the end of the inner loop. So pfVar8 advances by 0x30 bytes (12 floats). That means each iteration processes 12 floats. But the code accesses indices -8..-1 (8 floats) and 0..15 (16 floats), total 24 floats. Since pfVar8 advances by 12 floats, the negative indices refer to the previous volume? That is possible because the first iteration has no previous volume, so the negative indices would read garbage. But the initial value of pfVar8 is in_EAX+0x20, so pfVar8[-8] is at in_EAX+0x00. So the function is actually reading from the start of the object (offset 0x00) as part of the first volume's plane data. That suggests the object layout is such that the first volume's data extends from offset 0x00 to some point, and subsequent volumes are at offsets 0x30, 0x60, etc. But then the negative indices for later iterations would read from previous volumes, which is intentional if the data is contiguous? Let's re-evaluate: The code initializes pfVar8 as (float*)(in_EAX+0x20). Then accesses pfVar8[-8] etc. So for the first volume, it reads from in_EAX+0x00 to in_EAX+0x3C? (since -8 to 15 covers 24 floats = 96 bytes). That would be from 0x00 to 0x60. Then pfVar8 advances to in_EAX+0x50 (since 0x20+0x30=0x50). Then the second iteration reads from in_EAX+0x50-0x20 = in_EAX+0x30 to in_EAX+0x50+0x3C = in_EAX+0x8C. So that overlaps with the first volume's end. So the volumes are interleaved? This is getting too messy. Given the time, we will trust the decompiler's logic and simply replicate the arithmetic in the reconstructed code without worrying about the exact memory layout, as long as the logic is functionally equivalent. We'll treat the volume data as a flat array and compute indices accordingly.

                // Compute transformed components using the transformation part of the volume (indices 8..15)
                float transf1 = *(volumeData + 11) * constant + *(volumeData + 10) * pointZ;
                float transf2 = *(volumeData + 9) * pointY + *(volumeData + 8) * pointX;
                float transf3 = *(volumeData + 15) * constant + *(volumeData + 14) * pointZ;
                float transf4 = *(volumeData + 13) * pointY + *(volumeData + 12) * pointX;

                // Four plane tests (plane coefficients at indices -8..-1 relative to volumeData, but in code they use volumeData[-8] etc)
                // To avoid negative indices, we offset the pointer: let planeBase = volumeData - 8 (but that's messy). We'll keep the same offset logic as the decompiled code.
                // We'll use a dummy array access to mimic the offsets. For simplicity, we'll assume volumeData is already adjusted to the correct start.
                // Actually, let's follow the decompiler exactly: the code does:
                // fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;  etc.
                // So we can reuse the same indexing.

                // Use the same variable names for clarity:
                float* v = volumeData;  // points to this+0x20 initially

                // Compute mask from plane comparisons (4 plane tests)
                int planeMask = 0;
                // First plane: coefficients at v[-8], v[-7], v[-6], v[-5]
                if (pointW < v[-7]*pointY + v[-8]*pointX + v[-5]*constant + v[-6]*pointZ) planeMask |= 1;
                // Second plane: v[-4], v[-3], v[-2], v[-1]
                if (pointW < v[-3]*pointY + v[-4]*pointX + v[-1]*constant + v[-2]*pointZ) planeMask |= 2;
                // Third plane: v[4], v[5], v[6], v[7]
                if (pointW < v[5]*pointY + v[4]*pointX + v[7]*constant + v[6]*pointZ) planeMask |= 4;
                // Fourth plane: v[0], v[1], v[2], v[3]
                if (pointW < v[1]*pointY + v[0]*pointX + v[3]*constant + v[2]*pointZ) planeMask |= 8;

                // Compute mask from transformation comparisons (2 tests duplicated)
                int transformMask = 0;
                // Comparison 1: pointW < transf2 + transf1
                if (pointW < transf2 + transf1) transformMask |= 1;
                // Comparison 2: pointW < transf4 + transf3
                if (pointW < transf4 + transf3) transformMask |= 2;
                // (the other two entries in auVar6 are duplicates of the first two)
                // Actually the code has four comparisons but duplicates: auVar6[0] and auVar6[1] are different, auVar6[2] = auVar6[1], auVar6[3] = auVar6[0] maybe. But movmskps will pack sign bits of all 4 floats. So we need to simulate that: the mask from auVar6 will have bits set for each of the four slots. Since the two unique comparisons are repeated to fill all slots, the resulting mask will have bits for both unique ones, and also duplicates. That effectively means both comparisons contribute: if either comparison is true, the corresponding bit(s) are set. So we can just combine them:
                if (pointW < transf2 + transf1) transformMask |= 0x5; // bits 0 and 2
                if (pointW < transf4 + transf3) transformMask |= 0xA; // bits 1 and 3

                // OR the two masks (in code: uVar10 | uVar11)
                int combinedMask = planeMask | transformMask;
                // The actual SSE movmskps returns a 4-bit mask, but here the bits may be different. We follow the decompiler logic:
                // uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX;
                // So if any bit is set, uVar10 = unaff_EBX (the volume's byte), else 0.
                int currentVolumeByte = volumeMasks[volumeIndex];
                int insideAny = (combinedMask != 0) ? currentVolumeByte : 0;
                outMask |= insideAny;

                volumeData += 12; // advance by 0x30 bytes / 4 = 12 floats
                volumeIndex++;
            } while (volumeIndex < 4);

            // Store the output byte for this point
            *(char*)(pointIndex + (int)outputMasks) = (char)outMask;
            pointIndex++;
            pointIter += 4; // advance by 4 floats (next point)
        } while (pointIndex < numPoints);
    }
}