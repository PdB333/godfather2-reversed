// Xbox PDB: SM_PrimTexturedClass::SelectTextureMode
// FUNC_NAME: RenderManager::updateShadowAndFog
void __thiscall RenderManager::updateShadowAndFog(void* thisPtr, void* cameraPtr)
{
    // thisPtr offsets (assumed class RenderManager):
    // +0x10: projection matrix? (used in FUN_006103f0)
    // +0x30: view matrix?
    // +0x50: world matrix?
    // +0xb0: array of 3 shadow map texture pointers
    // +0xb8: fog color (maybe)
    // +0xbc: fog color (maybe)
    // +0xc0: callback function pointer (set by external)
    // +0xc4: callback param
    // +0xc8 (200): current camera handle
    // +0xcc: screen width (int)
    // +0xd0: screen height (int)
    // +0xd6: horizontal resolution divisor
    // +0xd8: vertical resolution divisor
    // +0xda: depth resolution divisor
    // +0xdc: shadow quality mode (0=low, 1=high?)

    int* thisAsInt = (int*)thisPtr;
    int* cameraAsInt = (int*)cameraPtr;

    // Process three shadow maps
    for (int i = 0; i < 3; i++)
    {
        // Transform shadow map texture coordinates? Calls a matrix multiply function.
        unsigned char transformBuffer[40]; // local_58
        FUN_00606fd0(*(int*)(thisAsInt + 0x2c + i), // offset +0xb0 = 0x2c in word units? Actually 0xb0/4 = 0x2c, but careful: thisAsInt is int*, so +0x2c is at byte offset 0xb0.
                     2, 0, transformBuffer); // FUN_00606fd0 likely multiplies by a matrix

        int uVar4 = *(int*)(cameraAsInt + 0x8 + i); // cameraPtr+0x20? Wait: cameraAsInt + 0x8 is offset 0x20? Actually 0x20/4=0x8. So cameraPtr + 0x20 + i*4.
        FUN_00614ed0(transformBuffer + 0x34, transformBuffer + 0x40, uVar4, uVar4); // local_14 and local_30 were at the end of the buffer, adjust offsets
        FUN_006071a0(transformBuffer); // Apply the transform back to something
    }

    // Compute fog start/end parameters from screen dimensions
    float fVar5 = (float)*(thisAsInt + 0x33); // +0xcc
    if (fVar5 < 0.0f) fVar5 += 0.5f; // DAT_00e44578 likely 0.5f for rounding
    float fVar6 = (float)*(thisAsInt + 0x34); // +0xd0
    if (fVar6 < 0.0f) fVar6 += 0.5f;

    unsigned short uVar1 = *(unsigned short*)((int)thisAsInt + 0xd6);
    unsigned short uVar2 = *(unsigned short*)((int)thisAsInt + 0xd8);
    unsigned short uVar3 = *(unsigned short*)((int)thisAsInt + 0xda);

    float fVar7 = fVar6 - 0.5f; // DAT_00e2cd54 is 0.5f
    // Calculate fog distances
    float fogStart = fVar7 / (float)uVar1;
    float fogEndX = (fVar5 * 0.5f - 0.5f) / (float)uVar2;
    float fogEndY = (fVar6 * 0.5f - 0.5f) / (float)uVar3;

    // Set global LOD bias from configuration
    int lodBias = FUN_0060a580(g_RegistrySomething, "lodBias"); // DAT_01127884 maybe a registry handle
    // Update some global LOD array (maybe per-level LOD bias table)
    if (g_SomeGlobalPtr == (int*)0x01127760) // DAT_012058e8
    {
        FUN_0060a460(g_SomeGlobal2); // might release something
        int* piVar8 = g_SomeGlobal3; // DAT_01205750
        if (lodBias != 0)
        {
            int index = lodBias & 0xff;
            bool isNegative = (lodBias & 0x80000000) != 0;
            float* pfVar11;
            if (!isNegative)
                pfVar11 = (float*)(&g_LodBiasTablePos + index * 4 * 4); // each entry 16 bytes (4 floats)
            else
                pfVar11 = (float*)(&g_LodBiasTableNeg + index * 4 * 4);

            if (*pfVar11 != g_LodBiasCurrentValue) // DAT_01127840
            {
                *pfVar11 = g_LodBiasCurrentValue;
                if (!isNegative)
                    (**(code**)(*piVar8 + 0x1b4))(piVar8, index, pfVar11, 1);
                else
                    (**(code**)(*piVar8 + 0x178))(); // different virtual call for negative
            }
        }
    }

    // Set fog parameters (color, start, end)
    FUN_00619a50(*(int*)(thisAsInt + 0x2e), // +0xb8
                 *(int*)(thisAsInt + 0x2f), // +0xbc
                 fogStart, fogEndX, fogEndY);

    // Store first shadow map globally
    g_CurrentShadowMap = *(int*)(thisAsInt + 0x2c); // DAT_011f4230 = *(this+0xb0)

    if (*(int*)(thisAsInt + 0x37) == 0) // +0xdc mode == 0
    {
        g_ShadowMapCount = 0; // DAT_011f4234
        // Clamp LOD levels
        if (g_MinLod < 0x1b) g_MinLod = 0x1b; // DAT_012058d0
        if (g_MaxLod > 0x1a) g_MaxLod = 0x1b; // DAT_00f15988
        g_SomeFlag = 1; // _DAT_011f3a44
        // Additional LOD clamp for mode 0
        if (g_MinLod < 7) g_MinLod = 7;
        if (g_MaxLod > 7) g_MaxLod = 7;
        g_AnotherFlag = 0; // _DAT_011f39f4
        // Update projection/view matrices
        FUN_006103f0(thisAsInt + 0x4, // +0x10
                     thisAsInt + 0x14, // +0x50
                     thisAsInt + 0xc); // +0x30
        // Reset flag and clamp again
        g_AnotherFlag = 1;
        if (g_MinLod < 7) g_MinLod = 7;
        if (g_MaxLod > 7) g_MaxLod = 7;
        g_AnotherFlag = 1; // Note: the original sets it again?
        // Final clamp
        if (g_MinLod < 0x1b) g_MinLod = 0x1b;
    }
    else if (*(int*)(thisAsInt + 0x37) == 1) // +0xdc mode == 1
    {
        g_ShadowMapCount = 1; // DAT_011f4234
        // Clamp LODs
        if (g_MinLod < 0x1b) g_MinLod = 0x1b;
        if (g_MaxLod > 0x1a) g_MaxLod = 0x1b;
        g_SomeFlag = 1;
        // Check if HDR or bloom is active
        if (FUN_004166b0() && (g_SomeEffectMask & 1) != 0)
        {
            FUN_00614a50(); // Apply some post-effect
        }
        // Update projection/view matrices
        FUN_006103f0(thisAsInt + 0x4, thisAsInt + 0x14, thisAsInt + 0xc);
        // Initialize a bunch of global float arrays (likely for tone mapping or color grading)
        g_SomeFloatArray[0] = 0.0f; // Actually set to DAT_00e2b1a4 (maybe 0.0)
        g_SomeFloatArray[1] = 0.0f;
        g_SomeFloatArray[2] = 0.0f;
        // ... many more initializations, all set to 0.0f
        // Check again for post-effect
        if (g_SomeEffectMask & 1)
            FUN_00614a50();
        // Final clamp
        if (g_MinLod < 0x1b) g_MinLod = 0x1b;
    }

    // Ensure max LOD is not too high
    if (g_MaxLod > 0x1a) g_MaxLod = 0x1b;
    g_SomeFlag = 0;

    // Store the camera pointer
    if (*(int*)(thisAsInt + 0x32) == 0) // +0xc8
    {
        *(int*)(thisAsInt + 0x32) = (int)cameraPtr;
        return;
    }
    if (*(int*)(thisAsInt + 0x30) != 0) // +0xc0
    {
        // Call a callback if present
        (**(code**)(*(int*)(thisAsInt + 0x30)))(*(int*)(thisAsInt + 0x32), *(int*)(thisAsInt + 0x31));
        *(int*)(thisAsInt + 0x32) = (int)cameraPtr;
        return;
    }
    *(int*)(thisAsInt + 0x32) = (int)cameraPtr;
    return;
}