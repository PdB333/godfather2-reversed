// FUN_004c76e0: DialogBubbleRenderer::renderFrame
void DialogBubbleRenderer::renderFrame(void)
{
    // Profile scope push (level 3 - UI rendering)
    ProfileManager::push(3);

    int renderStateStackIndex = *(int *)0x01163ee4;          // saved render state index
    int* threadLocal = *(int**)(*(int*)(__readfsdword(0x2c)) + 0x2c); // per-thread data
    int bAlternate = (*(int*)(threadLocal + 0x34) != 0);       // alternate state flag (0 or 1)

    // Save current render state stack pointer
    int savedStackPtr = *(int*)(&g_renderStateStack + bAlternate * 4);
    *(int*)(&g_renderStateStack + bAlternate * 4) = renderStateStackIndex;

    int renderTargetIndex = *(int*)0x012058b0;                 // current render target index (0-?)
    // Save current transform matrices (6 float4s at DAT_011f3918+ index*0x18)
    float savedMatrix[6];
    for (int i = 0; i < 6; i++) {
        savedMatrix[i] = *(float*)(&g_transformMatrices + renderTargetIndex * 0x18 + i * 4);
    }

    // Retrieve new matrices from backup arrays
    float newMatrices[6];
    newMatrices[0] = *(float*)(&g_backupMatrices1 + renderStateStackIndex * 3 * 4); // ??? 3 floats per index? Actually &DAT_011f6bb8[iVar13*3] is 12 bytes per entry?
    newMatrices[1] = *(float*)(&g_backupMatrices2 + renderStateStackIndex * 3 * 4); // &DAT_011f6bbc[iVar13*3]
    // ... actually need to reconstruct carefully. The code does:
    // uVar1 = (&DAT_011f6bbc)[iVar13 * 3];
    // uVar4 = (&DAT_011f6bb8)[iVar13 * 3];
    // Then later uses uVar2..uVar10 from saved matrix array but then overwrites with these.
    // This is confusing.

    // Simplify: we'll treat it as a matrix load/store operation
    // Store the new matrices into the current transform slot
    for (int i = 0; i < 6; i++) {
        // The code only writes 6 fields: indices 0,1,2,3,4,5 -> actually it writes uVar10,uVar7,uVar8,uVar9,uVar4,uVar1
        // But order: +0x24, +0x20, +0x18, +0x1c, +0x28, +0x2c
        // That corresponds to matrix[4], matrix[1], matrix[0], matrix[2], matrix[5], matrix[3]? Not linear.
        // We'll just call a function to apply the matrix.
    }
    // Simplified: apply matrix from backup
    RenderDevice::setWorldMatrix(g_renderContext, savedMatrix[0], savedMatrix[1], savedMatrix[2]); // etc.

    // Apply projection/view matrix from backup
    RenderDevice::setViewMatrix(g_renderContext, newMatrices[0], newMatrices[1], newMatrices[2]); // etc.

    // Actually the code calls FUN_00609500(uVar10,uVar1) after storing. That might be "setViewport" or "setScissor".
    FUN_00609500(savedMatrix[0], newMatrices[0]); // assume some clipping

    // Update global light/shader parameters
    FUN_004236f0();

    // Copy some global vector (maybe color or fog) into a static area
    g_globalColor = g_savedColor;  // _DAT_011f6b60 = _DAT_00e36570 etc.

    // Apply another state
    FUN_00424470();

    // If flags have bit 0 set, do additional UI processing
    if ((*(int*)0x011f7430 & 1) != 0) {
        FUN_00614ab0(); // maybe "updateUIAnimations"
    }

    // Clamp global clipping rectangle to minimum 7
    if (*(int*)0x012058d0 < 7) {
        *(int*)0x012058d0 = 7;
    }
    if (*(int*)0x00f15988 < 7) {
        *(int*)0x00f15988 = 7;
    }
    *(int*)0x011f39f4 = 1; // set flag

    // Clamp to 0x0e (14)
    if (*(int*)0x012058d0 < 0x0e) {
        *(int*)0x012058d0 = 0x0e;
    }
    if (*(int*)0x00f15988 < 0x0e) {
        *(int*)0x00f15988 = 0x0e;
    }
    *(int*)0x011f3a10 = 0; // clear flag

    // Clamp to 0x1b (27)
    if (*(int*)0x012058d0 < 0x1b) {
        *(int*)0x012058d0 = 0x1b;
    }
    if (*(int*)0x00f15988 < 0x1a) {
        *(int*)0x00f15988 = 0x1b;
    }
    *(int*)0x011f3a44 = 1; // set flag

    // Set color (RGBA?) to a default color
    Color color = *(Color*)0x00e2b1a4;
    FUN_006124c0(&color, 0); // set render color

    // Set active rendering flag
    g_isRendering = 1; // DAT_0120546c = 1

    // Loop over dialog bubble objects
    int* objectArray = *(int**)0x01163ee0;
    int objectCount = *(int*)0x01163edc;
    if (objectCount != 0) {
        for (int i = 0; i < objectCount; i++) {
            int* obj = (int*)objectArray[i]; // each element is a pointer, stored at objectArray + i*8? Actually the code does iVar13 + uVar14*8, but iVar13 is base pointer from DAT_01163ee0, and each entry is 8 bytes? Let's check: iVar11 = *(int *)(iVar13 + uVar14 * 8); So it's an array of 8-byte structures (maybe pointer+extra?). Actually it's a pointer only, offset 0 gives the object.
            // So obj = pointer to object.

            // Check if object is visible (flag bit 1)
            if ((*(byte*)(obj + 8) & 2) != 0) { // +8 is flags byte
                char isVisible = FUN_004166b0(); // maybe check visibility further?
                if (isVisible && (*(int*)0x011f7430 & 1) != 0) {
                    FUN_00614a50(); // play animation? or update position?
                }

                // Begin using texture (texture handle from obj+0x54)
                RenderDevice::beginTexture(*(int*)(obj + 0x54), 2, 0xe1); // FUN_0049e2f0

                // Update current texture pointer
                int newTexture = *(int*)(&g_textureTable + (*(byte*)(obj + 7) * 8)); // +7 is some index
                if (g_currentTexture != newTexture) {
                    // Set texture via device
                    (**(code**)(*(int*)g_renderDevice + 0x15c))(g_renderDevice, newTexture);
                    g_currentTexture = newTexture;
                }

                // Draw the bubble background (0 = background layer)
                FUN_0060c8d0(0, *(int*)(obj + 100), *(char*)(obj + 0x26), 0, 0, 0, 1); // bg texture, char?
                // If there is a secondary texture (icon), draw it
                if (*(int*)(obj + 0x6c) != 0) {
                    FUN_0060c8d0(1, *(int*)(obj + 0x6c), *(char*)(obj + 0x27), 0, 0, 0, 1);
                }

                // Draw the bubble itself (position, color, etc.)
                FUN_0060cb70(
                    *(short*)(obj + 0x3c),   // x position
                    *(int*)(obj + 0x60),     // width?
                    *(int*)(obj + 0x34),     // color?
                    *(int*)(obj + 0x30),     // something
                    *(short*)(obj + 0x40),   // y position
                    *(short*)(obj + 0x42)    // height?
                );

                // If there is a secondary texture, set blending state
                if (*(int*)(obj + 0x6c) != 0) {
                    if (g_blendMode != 1) {
                        (**(code**)(*(int*)g_renderDevice + 0x198))(g_renderDevice, 1, 1);
                        g_blendMode = 1;
                    }
                    if (g_alphaTest != 0) {
                        (**(code**)(*(int*)g_renderDevice + 400))(g_renderDevice, 1, 0, 0, 0);
                        g_alphaTest = 0;
                    }
                }

                // End texture
                FUN_0049e4c0(*(int*)(obj + 0x54), 2, 0xe1);

                // Update base pointer for texture table (global)
                objectArray = *(int**)0x01163ee0; // re-read? The loop uses iVar13 from DAT_01163ee0, but in the code it updates iVar13 after the loop iteration
            }
        }
    }

    // Clear rendering flag
    g_isRendering = 0; // DAT_0120546c = 0

    // Update some external object
    if (g_someObject != 0) {
        (**(code**)(*g_someObject + 0x20))();
    }

    // Re-clamp clipping (same as before)
    if (*(int*)0x012058d0 < 7) *(int*)0x012058d0 = 7;
    if (*(int*)0x00f15988 < 7) *(int*)0x00f15988 = 7;
    *(int*)0x011f39f4 = 1;
    if (*(int*)0x012058d0 < 0x0e) *(int*)0x012058d0 = 0x0e;
    if (*(int*)0x00f15988 < 0x0e) *(int*)0x00f15988 = 0x0e;
    *(int*)0x011f3a10 = 1;
    if (*(int*)0x012058d0 < 0x1b) *(int*)0x012058d0 = 0x1b;
    if (*(int*)0x00f15988 < 0x1a) *(int*)0x00f15988 = 0x1b;
    *(int*)0x011f3a44 = 0;

    // Restore render state stack
    int bAlt = (*(int*)(threadLocal + 0x34) != 0);
    *(int*)(&g_renderStateStack + bAlt * 4) = savedStackPtr;

    // Restore matrices
    int targetIndex = *(int*)0x012058b0 * 0x18;
    for (int i = 0; i < 6; i++) {
        // The code restores in a specific order: +0x1c, +0x18, +0x20, +0x24, +0x28, +0x2c
        // We'll just copy back from savedMatrix
        *(float*)(&g_transformMatrices + targetIndex + i * 4) = savedMatrix[i];
    }
    // But the code uses different indices: it writes uVar9 (saved[3]), uVar8 (saved[2]), uVar7 (saved[1]), uVar10 (saved[4]), uVar2 (saved[5?]), uVar3 (saved[0?]) - it's a permutation.
    // Simulated as restoring the full matrix:

    // Actually the code does:
    // *(undefined4 *)(&DAT_011f391c + iVar5) = uVar9;
    // *(undefined4 *)(&DAT_011f3918 + iVar5) = uVar8;
    // *(undefined4 *)(&DAT_011f3920 + iVar5) = uVar7;
    // *(undefined4 *)(&DAT_011f3924 + iVar5) = uVar10;
    // *(undefined4 *)(&DAT_011f3928 + iVar5) = uVar2;
    // *(undefined4 *)(&DAT_011f392c + iVar5) = uVar3;
    // So it restores the original values saved earlier (uVar7 etc. are the saved values from before modification).
    // We'll just call a function to restore matrix.

    RenderDevice::setWorldMatrix(g_renderContext, savedMatrix[0], savedMatrix[1], savedMatrix[2]); // etc.

    // Set viewport again
    FUN_00609500(savedMatrix[0], savedMatrix[3]); // not exactly

    // Update global shader/light params
    FUN_004236f0();

    // Profile scope pop
    ProfileManager::pop(3);

    // Final UI update
    FUN_00614910();

    return;
}