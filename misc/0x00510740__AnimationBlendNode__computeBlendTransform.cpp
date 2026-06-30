// FUNC_NAME: AnimationBlendNode::computeBlendTransform
void __thiscall AnimationBlendNode::computeBlendTransform(void *thisPtr, int inputData, int unusedParam, int outputMatrices)
{
    float sqrtVal;
    float *pfVar18;
    float *pfVar19;
    uint uVar13;
    uint uVar20;
    int iVar15;
    int iVar16;
    float fVar21;
    float fVar22;
    float fVar25;
    double dVar24;
    float fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    undefined4 uVar10, uVar11, uVar27;
    undefined4 *puVar1, *puVar17;
    char cVar2;
    byte *pbVar14;
    bool bBlendReady;
    int fsBase; // from FS segment

    // Get thread-local storage? (FS:0x2C)
    int *pTls = *(int **)(fsBase + 0x2c);
    // Probably a per-frame singleton call (might be getting a render context)
    // FUN_00414aa0 is likely a TLS/thread context getter
    // (ignore for reconstruction, but keep the calls as they are side effects)
    void *singleton1 = (void *)FUN_00414aa0(); // maybe getAnimationManager?
    // Set global pointer (some static base address)
    void *globalPtr = DAT_00e2b1a4; // likely 0 or identity
    void *someGlobal = DAT_00e2b1a4;
    FUN_00414aa0(); // another singleton call

    // Get the node data (offset 0x24 from this)
    int nodeData = *(int *)((int)thisPtr + 0x24);
    bBlendReady = false;

    // Check blend type flags: bit 0x4000 (0x4000) or 0x80000
    if ((*(uint *)(nodeData + 0x108) & 0x4000) == 0) {
        // Not additive blend
        if ((*(uint *)(nodeData + 0x10c) & 0x80000) == 0) {
            goto LAB_0051088e;
        }
        // Some other branch (maybe player transform blend)
        iVar15 = FUN_004e9fa0(); // getPlayer?
        // Select between player (index 1) and something else
        iVar15 = *(int *)((uint)(*(int *)(pTls[0x34]) != 0) * 0x98 + 0xc + iVar15);
        // Get translation from player transform
        undefined *px = *(undefined **)(iVar15 + 0x60); // offset 0x60: x
        float py = *(float *)(iVar15 + 100);             // offset 0x64: y (0x64)
        float pz = *(float *)(iVar15 + 0x68);            // offset 0x68: z
        undefined4 pw = *(undefined4 *)(iVar15 + 0x6c);  // offset 0x6c: w (homogeneous? usually 1)
        // Set local vector (using stack variables)
        float localVecX = (float)px;
        float localVecY = py;
        float localVecZ = pz;
        undefined4 localVecW = pw;
        // The code later uses local_80 as x, fStack_7c as y, fStack_78 as z? Actually reverse: local_80 is x? Let's check:
        // local_80 = in_XMM0_Da (which is px), fStack_7c = py, fStack_78 = pz, uStack_74 = pw
        // So local_80 = x, fStack_7c = y, fStack_78 = z, uStack_74 = w
        // But in the additive branch it computes differently.
        // We'll map them accordingly.
        // Actually the variable names are tricky; we'll rename for clarity.
        float blendPosX = (float)px;
        float blendPosY = py;
        float blendPosZ = pz;
        float blendPosW = 1.0f; // assuming identity
    }
    else {
        // Additive blend path: compute a normalized vector from some local data
        // local_70, local_6c, local_68 are used (likely input vector components)
        // These are from stack locals that are not initialized properly in decompiler; they come from the function's local storage.
        // In the original code, these are probably passed as part of the blend state.
        // For reconstruction, we'll treat them as local variables (the compiler used registers for the initial part)
        // Actually the decompiler shows:
        // fVar21 = local_68 * local_68 + (float)local_70 * (float)local_70 + (float)local_6c * (float)local_6c;
        // So local_68, local_70, local_6c are the input vector components.
        // But these are not set before use; they must come from uninitialized stack? Probably the decompiler couldn't track them.
        // Actually in the code, there is an earlier assignment to local_68, local_6c, local_70? Not shown.
        // Let's assume they are filled from the blend input (maybe from node data).
        // For reconstruction, we'll name them inputVecX, inputVecY, inputVecZ.
        // Also local_80 is used as the destination vector.
        // Compute magnitude
        float magSq = local_68 * local_68 + (float)local_70 * (float)local_70 + (float)local_6c * (float)local_6c;
        if (magSq <= DAT_00e2cbe0) { // epsilon check
            blendPosY = 0.0f; // originally fStack_7c
            magSq = 0.0f;
        } else {
            sqrtVal = SQRT(magSq);
            blendPosY = (float)globalPtr / sqrtVal; // globalPtr is likely 0 or identity? Actually it's used as a scalar.
        }
        // Normalize the vector
        blendPosX = (float)local_70 * blendPosY; // local_70 * (1/mag) -> x component
        blendPosZ = local_68 * blendPosY;         // z component
        blendPosY = blendPosY * (float)local_6c; // y component (note swap: local_6c is original y? Actually decompiler: fStack_7c = (float)local_6c * fStack_7c, so yes)
        float blendPosW_ = 0.0f; // uStack_74 = 0
        // Check if magnitude is less than some threshold
        if (sqrtVal < (float)PTR_FUN_00e4462c) {
            blendPosX = 0.0f;
            blendPosY = 0.0f;
            blendPosZ = 0.0f;
            // Use a single element based on a byte at nodeData+0x157
            // (&local_80)[*(char *)(iVar15 + 0x157)] = (undefined *)globalPtr;
            // This sets one component to globalPtr (probably 0 or 1)
            // This is obscure; we'll skip for now
        }
        // In the decompiler, local_80, fStack_7c, fStack_78 are the blended vector.
        // We'll treat local_80 as x, fStack_7c as y, fStack_78 as z, uStack_74 as w.
    }
    bBlendReady = true;

LAB_0051088e:
    // Call some function with inputData (param_2)
    FUN_0050a940(inputData);

    if (bBlendReady) {
        // Initialize a matrix (or quaternion?) on the stack
        // This part builds a 4x4 matrix? The stack variables are:
        // float fStack_4c;       // [SP+0x4C] ??
        // undefined4 uStack_48;
        // undefined4 uStack_44;
        // float local_40;
        // undefined4 uStack_38;
        // undefined4 uStack_34;
        // undefined4 local_30;
        // undefined4 uStack_2c;
        // undefined4 uStack_24;
        // Actually the structure is:
        // local_50: something (pointer)
        // fStack_4c: first float
        // uStack_48: second? etc.
        // local_40: float
        // etc.
        // There's also a call to FUN_00b99fcb (maybe sin) and FUN_00b99e20 (cos) with double conversion.
        // This looks like computing a rotation from angle.
        // We'll simplify: This block builds a transform matrix from the blend vector (position) and some rotations.
        // The matrix is then passed to other functions.

        // Zero out stack for matrix?
        fStack_4c = 0.0f;
        uStack_48 = 0;
        uStack_44 = 0;
        local_40 = 0.0f;
        uStack_38 = 0;
        uStack_34 = 0;
        local_30 = 0;
        uStack_2c = 0;
        uStack_24 = 0;

        // Convert blendPosX? Actually in this branch, the code uses in_XMM0_Da which holds some float (the first element of blend vector? But earlier it was the original px).
        // This is messy; we'll assume that the local_80, fStack_7c, fStack_78 represent the translation vector.
        // But the code also uses (float)in_XMM0_Da which is the first component of the blend vector (x).
        // We'll use blendPosX, blendPosY, blendPosZ.

        // Compute sin and cos of something (angle? maybe from magnitude?)
        dVar24 = (double)(float)blendPosX; // actually in_XMM0_Da is blendPosX
        float angle1 = (float)dVar24;
        FUN_00b99fcb(); // sin? (returns in st(0) but decompiler doesn't capture)
        // The code uses dVar24 again after the call; but the decompiler shows it's reused.
        // Actually there is a pattern: call sin, then call cos with same angle.
        // We'll approximate:
        float sinAngle = (float)FUN_00b99fcb(); // returns sin
        dVar24 = (double)(float)blendPosX;
        float cosAngle = (float)FUN_00b99e20(); // returns cos

        // Set fStack_4c (maybe element [0][0]) and local_40 (maybe element [1][1]?)
        fStack_4c = sinAngle;
        local_40 = DAT_00e44564 - fStack_4c; // DAT_00e44564 is likely 1.0f, so 1 - sinAngle

        // Set local_50 (pointer) to something global
        local_50 = (undefined *)(float)blendPosX; // reinterpret as pointer? This is odd.
        // Then set local_70, local_6c, local_68, local_64:
        local_70 = (undefined *)0x0;
        local_6c = DAT_00e2b1a4; // likely 0
        local_68 = 0.0f;
        local_64 = 0;
        // Then a condition on global DAT_00e44854 (maybe 0.0f) compared to something derived from fStack_7c (blendPosY) with a mask.
        if (DAT_00e44854 <= (float)((uint)blendPosY & DAT_00e44680)) {
            local_70 = DAT_00e2b1a4; // set to something
        }

        // Now call two matrix functions:
        // FUN_0056c6b0(&local_80, &local_70, outputMatrices); // local_80 is the first vector? Actually &local_80 is address of the combined vector.
        // FUN_0056b230(&local_50, outputMatrices, outputMatrices, 3); // &local_50 is a pointer to the matrix block.
        // Then set some elements of output matrix to 0.
        *(undefined4 *)(outputMatrices + 0xc) = 0; // row0 col3
        *(undefined4 *)(outputMatrices + 0x1c) = 0; // row1 col3
        *(undefined4 *)(outputMatrices + 0x2c) = 0; // row2 col3

        // If a flag in nodeData+0x104 & 2 is set, do another blend with additional data from thisPtr+0x10
        if ((*(byte *)(*(int *)((int)thisPtr + 0x24) + 0x104) & 2) != 0) {
            FUN_0056b230(outputMatrices, *(int *)((int)thisPtr + 0x10) + 0x50 + *(int *)(pTls[0x8]), outputMatrices, 3);
            // Clear again
            *(undefined4 *)(outputMatrices + 0xc) = 0;
            *(undefined4 *)(outputMatrices + 0x1c) = 0;
            *(undefined4 *)(outputMatrices + 0x2c) = 0;
        }
    } else {
        // Non-blend path (bBlendReady false)
        iVar15 = *(int *)((int)thisPtr + 0x24);
        cVar2 = *(char *)(iVar15 + 0x157); // index into bone array
        uVar13 = 0x21 >> (cVar2 * 4 & 0x1f) & 0xf; // lookup?
        uVar20 = 0x21 >> ((char)uVar13 * 4 & 0x1f) & 0xf; // another derived index

        if ((*(byte *)(iVar15 + 0x104) & 2) == 0) {
            // Simply call a function with current data
            FUN_0056bf40(in_XMM0_Da); // in_XMM0_Da might be from earlier? Actually not set in this path. Probably unused.
        } else {
            // Complex matrix multiplication with weighted blend
            dVar24 = (double)blendPosX; // same issue
            float weight1 = (float)dVar24;
            FUN_00b99fcb(); // sin?
            dVar24 = (double)blendPosX;
            float weight2 = (float)dVar24;
            // Compute address of source matrices from thisPtr+0x10 and TLS
            puVar17 = (undefined4 *)((cVar2 + 5) * 0x10 + *(int *)((int)thisPtr + 0x10) + *(int *)(pTls[0x8]));
            // Copy source matrix to output at index cVar2
            uVar27 = puVar17[1];
            uVar10 = puVar17[2];
            uVar11 = puVar17[3];
            puVar1 = (undefined4 *)(cVar2 * 0x10 + outputMatrices);
            *puVar1 = *puVar17;
            puVar1[1] = uVar27;
            puVar1[2] = uVar10;
            puVar1[3] = uVar11;
            // Now blend with another source matrix at index uVar20+5, scaled by weight1
            iVar15 = (uVar20 + 5) * 0x10;
            pfVar18 = (float *)(*(int *)((int)thisPtr + 0x10) + iVar15 + *(int *)(pTls[0x8]));
            fVar21 = *pfVar18;
            fVar4 = pfVar18[1];
            fVar5 = pfVar18[2];
            fVar6 = pfVar18[3];
            pfVar18 = (float *)(uVar13 * 0x10 + outputMatrices);
            *pfVar18 = weight1 * fVar21;
            pfVar18[1] = weight1 * fVar4;
            pfVar18[2] = weight1 * fVar5;
            pfVar18[3] = weight1 * fVar6;
            // Now blend with another source matrix at index uVar13+5, scaled by weight2, and add to previous result
            float oneMinusWeight1 = DAT_00e44564; // 1.0f
            iVar16 = (uVar13 + 5) * 0x10;
            pfVar19 = (float *)(*(int *)((int)thisPtr + 0x10) + iVar16 + *(int *)(pTls[0x8]));
            fVar7 = pfVar19[1];
            fVar8 = pfVar19[2];
            fVar9 = pfVar19[3];
            *pfVar18 = *pfVar19 * weight2 + weight1 * fVar21; // but note: fVar21 is reused? Actually after first assignment, pfVar18 points to output, and we are overwriting it again. This is a double blend.
            pfVar18[1] = fVar7 * weight2 + weight1 * fVar4;
            pfVar18[2] = fVar8 * weight2 + weight1 * fVar5;
            pfVar18[3] = fVar9 * weight2 + weight1 * fVar6;
            // Then do a similar blend for the second output index (uVar20)
            pfVar18 = (float *)(*(int *)((int)thisPtr + 0x10) + iVar15 + *(int *)(pTls[0x8]));
            pfVar19 = (float *)(uVar20 * 0x10 + outputMatrices);
            fVar21 = *pfVar18;
            fVar4 = pfVar18[1];
            fVar5 = pfVar18[2];
            fVar6 = pfVar18[3];
            *pfVar19 = fVar21 * weight2;
            pfVar19[1] = fVar4 * weight2;
            pfVar19[2] = fVar5 * weight2;
            pfVar19[3] = fVar6 * weight2;
            float oneMinusWeight2 = oneMinusWeight1 - weight1; // 1 - weight1
            pfVar18 = (float *)(*(int *)((int)thisPtr + 0x10) + iVar16 + *(int *)(pTls[0x8]));
            fVar7 = pfVar18[1];
            fVar8 = pfVar18[2];
            fVar9 = pfVar18[3];
            *pfVar19 = oneMinusWeight2 * *pfVar18 + fVar21 * weight2;
            pfVar19[1] = oneMinusWeight2 * fVar7 + fVar4 * weight2;
            pfVar19[2] = oneMinusWeight2 * fVar8 + fVar5 * weight2;
            pfVar19[3] = oneMinusWeight2 * fVar9 + fVar6 * weight2;
        }
    }

    // Check a flag in the base data (from param_1+0x10 + TLS offset)
    pbVar14 = (byte *)(*(int *)((int)thisPtr + 0x10) + *(int *)(pTls[0x8]));
    if ((*pbVar14 & 4) != 0) {
        // If flag set, call another function to modify output
        FUN_0056b420(pbVar14 + 0x50, &local_60, outputMatrices + 0x30);
        return;
    }
    // Otherwise copy some local_60 to output at offset 0x30
    *(undefined4 *)(outputMatrices + 0x30) = local_60;
    *(undefined4 *)(outputMatrices + 0x34) = uStack_5c;
    *(undefined4 *)(outputMatrices + 0x38) = uStack_58;
    *(undefined **)(outputMatrices + 0x3c) = puStack_54;
    return;
}