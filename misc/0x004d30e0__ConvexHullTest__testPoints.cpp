// FUNC_NAME: ConvexHullTest::testPoints
void __thiscall ConvexHullTest::testPoints(int thisPtr, float* points, char* outputMasks, int pointCount)
{
    // Constants and local variables
    float someConstant = DAT_00e2b1a4; // Global constant, likely 1.0f or similar
    byte shapeMasks[4]; // Masks for each shape (from offsets 0x60, 0x120, 0x1e0, 0x2a0)
    shapeMasks[0] = *(byte*)(thisPtr + 0x60);
    shapeMasks[1] = *(byte*)(thisPtr + 0x120);
    shapeMasks[2] = *(byte*)(thisPtr + 0x1e0);
    shapeMasks[3] = *(byte*)(thisPtr + 0x2a0);

    int currentPoint = 0;
    if (pointCount > 0) {
        float* pointPtr = points + 2; // Start at points[2]? Actually points+8 bytes? Wait, param_1+8 is the start of the first point's data? The code uses pfVar13 = (float*)(param_1 + 8) and then reads pfVar13[-2], pfVar13[-1], *pfVar13, pfVar13[1]. So the actual point data is at param_1, but the pointer is offset by 8 bytes? That suggests the structure at param_1 has a header of 8 bytes? Or maybe param_1 points to an array of structures where each structure has 4 floats but the pointer is incremented by 4 floats each iteration? Actually pfVar13 starts at param_1+8 and increments by 4 floats each iteration. So the first point is at param_1+8-8 = param_1? That would be at param_1, but then the next point is at param_1+8+4*4 = param_1+24? That's inconsistent. Let's re-examine: pfVar13 = (float*)(param_1 + 8); then in the loop, it reads pfVar13[-2], pfVar13[-1], *pfVar13, pfVar13[1]. So the four floats are at offsets -8, -4, 0, 4 from pfVar13. That means the first point's floats are at param_1+0, param_1+4, param_1+8, param_1+12. Then after processing, pfVar13 += 4 (i.e., advance by 16 bytes). So the next point's floats are at param_1+16, param_1+20, param_1+24, param_1+28. So the points are stored as contiguous 4-float arrays. So param_1 is the base address of the first point. The code uses param_1+8 as the starting pointer for the third float? Actually it's just a way to index. So we can treat points as float* pointing to the first float of the first point. The loop reads four floats per point: x, y, z, w? We'll call them pointX, pointY, pointZ, pointW.

        // Loop over each point
        for (int i = 0; i < pointCount; i++) {
            float pointX = points[i*4 + 0];
            float pointY = points[i*4 + 1];
            float pointZ = points[i*4 + 2];
            float pointW = points[i*4 + 3]; // The value compared against plane equations

            int combinedMask = 0;
            float* planeDataBase = (float*)(thisPtr + 0x20); // Base of plane data for first shape

            // Iterate over 4 shapes
            for (int shapeIdx = 0; shapeIdx < 4; shapeIdx++) {
                // Compute dot products for the two sets of planes (6 planes total)
                // First set: 4 planes (indices -8 to -5? Actually the code uses pfVar8[-8] to pfVar8[-1] for the first set? Let's map)
                // The code computes:
                // fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;  // pfVar8[10] and [11] are part of the second set?
                // fVar15 = pfVar8[9] * fVar2 + pfVar8[8] * fVar1;
                // fVar16 = pfVar8[0xf] * fVar7 + pfVar8[0xe] * fVar3;
                // fVar17 = pfVar8[0xd] * fVar2 + pfVar8[0xc] * fVar1;
                // Then first comparison: fVar4 < pfVar8[-7]*fVar2 + pfVar8[-8]*fVar1 + pfVar8[-5]*fVar7 + pfVar8[-6]*fVar3
                // Second: fVar4 < pfVar8[-3]*fVar2 + pfVar8[-4]*fVar1 + pfVar8[-1]*fVar7 + pfVar8[-2]*fVar3
                // Third: fVar4 < pfVar8[5]*fVar2 + pfVar8[4]*fVar1 + pfVar8[7]*fVar7 + pfVar8[6]*fVar3
                // Fourth: fVar4 < pfVar8[1]*fVar2 + *pfVar8*fVar1 + pfVar8[3]*fVar7 + pfVar8[2]*fVar3
                // Then second set: fVar4 < fVar15 + fVar14 (two times) and fVar4 < fVar17 + fVar16 (two times)

                // We'll compute these using SSE-like logic but in C++ for clarity.
                float* pf = planeDataBase; // pfVar8

                // First set of 4 plane tests
                bool test0 = pointW < (pf[-7]*pointY + pf[-8]*pointX + pf[-5]*someConstant + pf[-6]*pointZ);
                bool test1 = pointW < (pf[-3]*pointY + pf[-4]*pointX + pf[-1]*someConstant + pf[-2]*pointZ);
                bool test2 = pointW < (pf[5]*pointY + pf[4]*pointX + pf[7]*someConstant + pf[6]*pointZ);
                bool test3 = pointW < (pf[1]*pointY + pf[0]*pointX + pf[3]*someConstant + pf[2]*pointZ);

                // Compute the dot products for the second set
                float dot1 = pf[9]*pointY + pf[8]*pointX;
                float dot2 = pf[11]*someConstant + pf[10]*pointZ;
                float dot3 = pf[13]*pointY + pf[12]*pointX;
                float dot4 = pf[15]*someConstant + pf[14]*pointZ;

                // Second set of 2 plane tests (duplicated to 4)
                bool test4 = pointW < (dot1 + dot2);
                bool test5 = pointW < (dot3 + dot4);
                // The code duplicates these: test4 and test5 each appear twice in the mask

                // Combine masks using movmskps logic: each test contributes a bit
                int mask1 = (test0 ? 1 : 0) | (test1 ? 2 : 0) | (test2 ? 4 : 0) | (test3 ? 8 : 0);
                int mask2 = (test4 ? 1 : 0) | (test5 ? 2 : 0) | (test4 ? 4 : 0) | (test5 ? 8 : 0); // Duplicated

                // If any test in either set passes, the point is inside this shape
                int shapeMask = (mask1 | mask2) > 0 ? shapeMasks[shapeIdx] : 0;
                combinedMask |= shapeMask;

                // Move to next shape's plane data (each shape's plane data is 0x30 bytes apart)
                planeDataBase += 0x30 / sizeof(float); // 12 floats
            }

            outputMasks[i] = (char)combinedMask;
        }
    }
}