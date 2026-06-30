// FUNC_NAME: Matrix4x4::buildOrientationMatrix
void Matrix4x4::buildOrientationMatrix(void)
{
    // Stack locals for temporary vectors (4 floats each)
    float vecA[4]; // local_90, fStack_8c, fStack_88, fStack_84
    float vecB[4]; // local_80, fStack_7c, fStack_78, (unused)
    float vecC[4]; // local_70, fStack_6c, fStack_68, (unused)
    float vecD[4]; // local_20, fStack_1c, fStack_18, fStack_14

    // Call to fill vecA (likely a quaternion or direction from some source)
    FUN_0044c1a0(vecA);

    // Global constants (likely 1.0, 0.0, epsilon)
    float one = DAT_00e2b1a4;      // +0x00e2b1a4
    float epsilon = DAT_00e2cbe0;  // +0x00e2cbe0
    float scale = DAT_00e2eff4;    // +0x00e2eff4

    // First set of three vectors (rows?) at offsets 0x120, 0x130, 0x140
    float* dest1 = (float*)(this + 0x12c); // +0x12c
    for (int i = 0; i < 3; i++) {
        dest1[-3] = vecA[0];
        dest1[-2] = vecA[1];
        dest1[-1] = vecA[2];
        dest1[0] = vecA[3];
        dest1[0] = one; // overwrite last component
        dest1 += 4;
    }

    // Second set of three vectors at offsets 0x150, 0x160, 0x170
    float* dest2 = (float*)(this + 0x15c); // +0x15c
    for (int i = 0; i < 3; i++) {
        dest2[-3] = vecD[0];
        dest2[-2] = vecD[1];
        dest2[-1] = vecD[2];
        dest2[0] = vecD[3];
        dest2[0] = one;
        dest2 += 4;
    }

    // Compute direction vectors from differences
    float diffX = vecB[0] - vecA[0];
    float diffY = vecB[1] - vecA[1];
    float diffZ = vecB[2] - vecA[2];
    float lenSq = diffX*diffX + diffY*diffY + diffZ*diffZ;
    float invLen;
    if (lenSq <= epsilon) {
        invLen = 0.0f;
    } else {
        invLen = one / sqrtf(lenSq);
    }
    // Store first normalized direction at +0x180
    *(float*)(this + 0x180) = diffX * invLen;
    *(float*)(this + 0x184) = diffY * invLen;
    *(float*)(this + 0x188) = diffZ * invLen;

    // Second difference
    float diffX2 = vecC[0] - vecA[0];
    float diffY2 = vecC[1] - vecA[1];
    float diffZ2 = vecC[2] - vecA[2];
    float lenSq2 = diffX2*diffX2 + diffY2*diffY2 + diffZ2*diffZ2;
    float invLen2;
    if (lenSq2 <= epsilon) {
        invLen2 = 0.0f;
    } else {
        invLen2 = one / sqrtf(lenSq2);
    }
    // Store second normalized direction at +0x194, +0x198, +0x190? Actually +0x190 is 400 decimal
    *(float*)(this + 0x194) = diffY2 * invLen2; // note: swapped? original: fStack_6c * fVar6
    *(float*)(this + 0x198) = diffZ2 * invLen2; // original: fStack_68 * fVar6
    *(float*)(this + 0x190) = diffX2 * invLen2; // original: local_70 * fVar6

    // Compute cross product of the two normalized directions
    float* dir1 = (float*)(this + 0x180);
    float* dir2 = (float*)(this + 0x190); // actually second direction starts at 0x190? but we wrote to 0x194,0x198,0x190; so it's not contiguous
    // Let's assume the second direction is stored as (x at 0x190, y at 0x194, z at 0x198)
    float crossX = dir2[1] * dir1[2] - dir2[2] * dir1[1];
    float crossY = dir2[2] * dir1[0] - dir2[0] * dir1[2];
    float crossZ = dir2[0] * dir1[1] - dir2[1] * dir1[0];
    *(float*)(this + 0x1a0) = crossX;
    *(float*)(this + 0x1a4) = crossY;
    *(float*)(this + 0x1a8) = crossZ;

    // Set fourth component of cross product vector (unused, overwritten later)
    float temp = *(float*)(this + 0x1ac);
    *(float*)(this + 0x1ac) = *(float*)(this + 0x19c) * *(float*)(this + 0x18c) - *(float*)(this + 0x19c) * *(float*)(this + 0x18c);
    *(float*)(this + 0x1ac) = temp; // restore original? Actually it's overwritten

    // Scale and store matrix rows (4x4 matrix at +0x1b0 to +0x1dc)
    // First row: scale of first direction
    *(float*)(this + 0x1b0) = scale * *(float*)(this + 0x180);
    *(float*)(this + 0x1b4) = scale * *(float*)(this + 0x184);
    *(float*)(this + 0x1b8) = scale * *(float*)(this + 0x188);
    *(float*)(this + 0x1bc) = scale * *(float*)(this + 0x18c);
    *(float*)(this + 0x1bc) = one; // overwrite

    // Second row: scale of second direction
    *(float*)(this + 0x1c0) = scale * *(float*)(this + 0x190);
    *(float*)(this + 0x1c4) = scale * *(float*)(this + 0x194);
    *(float*)(this + 0x1c8) = scale * *(float*)(this + 0x198);
    *(float*)(this + 0x1cc) = scale * *(float*)(this + 0x19c);
    *(float*)(this + 0x1cc) = one; // overwrite

    // Third row: scale of cross product
    *(float*)(this + 0x1d0) = scale * *(float*)(this + 0x1a0);
    *(float*)(this + 0x1d4) = scale * *(float*)(this + 0x1a4);
    *(float*)(this + 0x1d8) = scale * *(float*)(this + 0x1a8);
    *(float*)(this + 0x1dc) = scale * *(float*)(this + 0x1ac);
    *(float*)(this + 0x1dc) = one; // overwrite

    // Set fourth components of the three direction vectors to 1.0
    *(float*)(this + 0x18c) = one;
    *(float*)(this + 0x19c) = one;
    *(float*)(this + 0x1ac) = one;
    *(float*)(this + 0x1bc) = one;
    *(float*)(this + 0x1cc) = one;
    *(float*)(this + 0x1dc) = one;
}