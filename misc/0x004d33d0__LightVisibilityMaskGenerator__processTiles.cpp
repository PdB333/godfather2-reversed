// FUNC_NAME: LightVisibilityMaskGenerator::processTiles
// Address: 0x004d33d0
// This function generates per-tile light visibility masks by testing 2D tile bounding boxes (or view-space AABBs)
// against up to 6 light frustums. The result is a byte array where each bit indicates which lights affect the tile.
// The function uses SIMD (SSE) half-space tests.

void __thiscall LightVisibilityMaskGenerator::processTiles(void* this, byte* outMask, int numTiles, int param_3) {
    float constantF = DAT_00e2b1a4;  // global constant, likely far plane or similar
    int iTile;
    int lightIndex;

    // Pre-fetch light enable flags from 6 light slots (each 0xC0 bytes apart)
    byte lightEnable[6];
    lightEnable[0] = *(byte*)((int)this + 0x60);
    lightEnable[1] = *(byte*)((int)this + 0x120);
    lightEnable[2] = *(byte*)((int)this + 0x1E0);
    lightEnable[3] = *(byte*)((int)this + 0x2A0);
    lightEnable[4] = *(byte*)((int)this + 0x360);
    lightEnable[5] = *(byte*)((int)this + 0x420);

    iTile = 0;
    if (0 < numTiles) {
        float* tileData = (float*)((int)param_1 + 8);  // per-tile data: 4 floats (minX, minY, maxX, maxY? or similar)
        uint currentLightMask = (uint)lightEnable[5];  // initially unused, but reused as scratch

        do {
            float minX = tileData[-2];
            float minY = tileData[-1];
            float maxX = tileData[0];
            float maxY = tileData[1];

            uint tileMask = 0;
            lightIndex = 0;
            float* lightPlaneData = (float*)((int)this + 0x20);

            do {
                // Each light frustum is represented by a set of planes.
                // Here we test the tile against two sets of 4 half-spaces (probably left/right/top/bottom and near/far?).
                float dot1 = lightPlaneData[8] * minX + lightPlaneData[9] * minY;
                float dot2 = lightPlaneData[10] * maxX + lightPlaneData[11] * constantF;
                // Actually careful: the decompiled code uses fVar1 = pfVar13[-2] (minX?), fVar2 = pfVar13[-1] (minY?),
                // fVar3 = *pfVar13 (maxX?), fVar4 = pfVar13[1] (maxY?), and fVar7 = constantF.
                // Then it computes:
                // fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;   // pfVar8[10] and [11]?
                // fVar15 = pfVar8[9] * fVar2 + pfVar8[8] * fVar1;
                // fVar16 = pfVar8[0xf] * fVar7 + pfVar8[0xe] * fVar3;
                // fVar17 = pfVar8[0xd] * fVar2 + pfVar8[0xc] * fVar1;
                // Then the sums: fVar15+fVar14 and fVar17+fVar16.
                // This suggests two dot products per corner. For simplicity, I'll inline the tests.

                // First set of 4 half-space tests (plane equations)
                // Compare maxY against:
                //   lightPlaneData[-7]*minY + lightPlaneData[-8]*minX + lightPlaneData[-5]*constantF + lightPlaneData[-6]*maxX
                // and similarly for plane[-3], plane[5], plane[1] (using offsets from lightPlaneData)
                // This creates a 4-bit mask uVar11 using movmskps.

                // Second set: compare maxY against (fVar15+fVar14) and (fVar17+fVar16), producing a 2-bit mask.
                // Then combine masks and AND with the light's enable bit.

                uint testResult1 = ... // computed via movmskps on four comparisons
                uint testResult2 = ... // computed via movmskps on two comparisons (duplicated)
                uint lightBit = (uint)lightEnable[lightIndex];
                uint combined = (0 < (int)(testResult1 | testResult2)) - 1;  // all ones if any test passes
                uint mask = combined & lightBit;
                tileMask |= mask;

                lightIndex++;
                lightPlaneData += 0x30;  // 12 floats stride (0x30 bytes)
            } while (lightIndex < 6);

            outMask[iTile] = (byte)tileMask;
            iTile++;
            tileData += 4;
        } while (iTile < numTiles);
    }

    return;
}