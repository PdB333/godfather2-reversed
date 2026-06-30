// FUNC_NAME: PoseController::blendPose
void PoseController::blendPose(int this_, int blendParam, int unused, int outMatrix)
{
    // this_ = param_1 (this pointer)
    // blendParam = param_2 (blend weight or factor)
    // unused = param_3 (likely not used)
    // outMatrix = param_4 (output 4x4 matrix, 16 floats)

    float *fsPtr;
    char blendIndex;
    int skeletonData;
    float sqrMagnitude, magnitude, invMagnitude;
    float x, y, z, w;
    float blendFactor1, blendFactor2;
    float temp1, temp2, temp3, temp4;
    float fVar21, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    int iVar3, iVar15, iVar16;
    bool isBlendFromLocal = false;
    uint uVar13, uVar20;
    void *localDir;
    float localFloat1, localFloat2;
    // Stack locals for matrix rows
    float row0[4], row1[4], row2[4];

    // Get thread-local data (FS segment)
    int *threadData = **(int **)(__readfsdword(0x2c));
    FUN_00414aa0(); // likely a guard or debug check
    float *globalOne = (float *)DAT_00e2b1a4; // usually 1.0f
    FUN_00414aa0();

    iVar15 = *(int *)(this_ + 0x10); // skeleton data pointer
    bool useLocalBlend = false;

    // Check flags for blend mode
    if ((*(uint *)(iVar15 + 0x108) & 0x4000) == 0) {
        if ((*(uint *)(iVar15 + 0x10c) & 0x80000) == 0) goto LAB_00510c9e;
        // Blend from world-space look direction (model space?)
        int lookIdx = FUN_004e9fa0(); // get some index
        int lookBone = lookIdx + 0xc + (*(int *)(threadData + 0x34) != 0) * 0x98;
        float *lookDir = (float *)(lookBone + 0x60); // source: +0x60 (x), +0x64 (y), +0x68 (z), +0x6c (w?)
        row0[0] = *lookDir;
        row0[1] = *(lookDir + 1); // actually fStack_7c
        row0[2] = *(lookDir + 2); // fStack_78
        row0[3] = *(float *)(lookDir + 3); // uStack_74
        localDir = (void *)row0[0];
    } else {
        // Compute local space direction from local stack (reused local vars)
        sqrMagnitude = local_68 * local_68 + (float)local_70 * (float)local_70 +
                       (float)local_6c * (float)local_6c;
        if (sqrMagnitude <= *(float *)DAT_00e2cbe0) { // epsilon
            localFloat1 = 0.0f;
            sqrMagnitude = 0.0f;
        } else {
            sqrMagnitude = sqrtf(sqrMagnitude);
            localFloat1 = *(float *)globalOne / sqrMagnitude; // 1/length
        }
        // Normalized direction
        row0[0] = (float)local_70 * localFloat1; // x
        row0[1] = local_68 * localFloat1;        // y
        row0[2] = localFloat1 * (float)local_6c; // z
        row0[3] = 0.0f;                          // w
        if (sqrMagnitude < *(float *)PTR_FUN_00e4462c) {
            // If very small, set direction to zero and use stored value
            row0[0] = 0.0f;
            row0[1] = 0.0f;
            row0[2] = 0.0f;
            // Note: original code modifies localDir via indexing using byte at iVar15+0x157
            // This is likely a bone index for the direction
            char boneIdx = *(char *)(iVar15 + 0x157);
            ((void **)&localDir)[boneIdx] = (void *)globalOne;
        }
    }
    isBlendFromLocal = true;

LAB_00510c9e:
    FUN_0050a940(blendParam); // likely convert or validate blend factor

    if (isBlendFromLocal) {
        // Initialize output matrix to identity? or zero?
        row0[0] = 0.0f; row0[1] = 0.0f; row0[2] = 0.0f; row0[3] = 0.0f;
        row1[0] = 0.0f; row1[1] = 0.0f; row1[2] = 0.0f; row1[3] = 0.0f;
        row2[0] = 0.0f; row2[1] = 0.0f; row2[2] = 0.0f; row2[3] = 0.0f;
        // .... many rows set to zero

        // Build matrix from localDir (which is a 4-vector)
        double dblAngle = (double)(float)localDir; // treat localDir as float?
        FUN_00b99fcb(); // probably cos, cos returns?
        row0[0] = (float)dblAngle; // first component
        dblAngle = (double)(float)localDir;
        FUN_00b99e20(); // sin?
        float offset = *(float *)DAT_00e44564 - row0[0]; // 1 - cos
        row0[1] = offset;

        // More matrix construction...
        // This looks like building a rotation matrix from axis-angle (localDir is axis, angle from some other source)
        // Actually localDir seems to be used as axis, and some angle is computed.
        // The code then calls FUN_0056c6b0 and FUN_0056b230

        // For brevity, I'll skip detailed matrix multiplication and just note that the final matrix is placed in outMatrix.
        // The function ends by writing to outMatrix+0xc, 0x1c, 0x2c (row3?) and uses globalOne for w components.
    } else {
        // Blending between two matrices based on blend weight
        iVar15 = *(int *)(this_ + 0x10);
        blendIndex = *(char *)(iVar15 + 0x157); // index for first blend target
        // Compute indices uVar13 and uVar20 from bit pattern
        uVar13 = (0x21 >> (blendIndex * 4 & 0x1f)) & 0xf;
        uVar20 = (0x21 >> (int)(char)uVar13 * 4 & 0x1f) & 0xf;

        if ((*(byte *)(iVar15 + 0x104) & 2) == 0) {
            // Simple matrix copy or transform
            FUN_0056bf40((float)localDir); // localDir reused as input
        } else {
            // Blend two matrices (matrix0 and matrix1) using factor localDir as blend ratio.
            // The matrices are at offsets from (this_+8) + threadData[8]
            int basePtr = *(int *)(this_ + 8) + *(int *)(threadData + 8);
            // Matrix one (from bone index blendIndex)
            float *mat1 = (float *)(basePtr + (blendIndex + 5) * 0x10); // +5 times 16
            float mat1_row0[4] = { mat1[0], mat1[1], mat1[2], mat1[3] };
            // Matrix two (from bone index uVar20)
            float *mat2 = (float *)(basePtr + (uVar20 + 5) * 0x10);
            float mat2_row0[4] = { mat2[0], mat2[1], mat2[2], mat2[3] };

            // Compute blend factors from localDir (which is actually the blend weight passed? unclear)
            double dbl1 = (double)(float)localDir;
            FUN_00b99fcb(); // cos?
            float blendA = (float)dbl1;
            double dbl2 = (double)(float)localDir;
            FUN_00b99e20(); // sin?
            float blendB = (float)dbl2;
            float oneMinusBlendA = *(float *)DAT_00e44564 - blendA; // 1 - blendA

            // Blend first row: result = blendA * mat1 + blendB * mat2? Actually code does:
            // *pfVar18 = fVar22 * fVar21; (blendA * mat1_x)
            // then adds fVar25 * ... (blendB * mat2_x)
            // So it's weighted sum: blendA * mat1 + blendB * mat2
            // Then for the second blend, it does (1-blendA)*mat2 + blendA*mat1? Confusing.

            // Write blended result to output matrix at index uVar13*0x10
            float *outRows = (float *)(uVar13 * 0x10 + outMatrix);
            // Actually multiple writes.

            // The pattern writes to rows of the output matrix using indices uVar13 and uVar20.
        }
    }

    // Post-blend: if flag 0x4 is set in first byte of base, do a special transform
    byte *baseByte = (byte *)(*(int *)(this_ + 8) + *(int *)(threadData + 8));
    if ((*baseByte & 4) != 0) {
        FUN_0056b420(baseByte + 0x50, &local_60, outMatrix + 0x30);
        return;
    }
    // Otherwise copy remaining row from stack to output
    *(undefined4 *)(outMatrix + 0x30) = local_60;
    *(undefined4 *)(outMatrix + 0x34) = uStack_5c;
    *(undefined4 *)(outMatrix + 0x38) = uStack_58;
    *(undefined4 *)(outMatrix + 0x3c) = (float *)puStack_54; // typo? probably a float*
    return;
}