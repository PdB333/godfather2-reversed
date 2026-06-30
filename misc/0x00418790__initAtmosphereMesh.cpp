// FUNC_NAME: initAtmosphereMesh
void __fastcall initAtmosphereMesh(void* pContext)
{
    // +0x8: some flag initialized to 0
    *(uint*)((int)pContext + 8) = 0;

    if (g_pSkyVertexAlloc == nullptr)
    {
        // Allocate vertex buffer: 0x360 bytes = 0x54 vertices? Each vertex: 3 floats? 0x54*12=0x3F0, not exact.
        // Actually 0x360/12 = 0x48 vertices (72). We'll compute later.
        g_pSkyVertexAlloc = (undefined4*)allocMem(0x360, 0, 0, 0x12);
        // Allocate index buffer: 0xb2 shorts = 0x164 bytes? 0xb2=178, times 2=356=0x164.
        g_pSkyIndexAlloc = (undefined4*)allocMem(0xb2, 0, 0, 0x12);

        // Lock vertex buffer
        if (*(char*)((int)g_pSkyVertexAlloc + 7) == '\0')
        {
            // +0x1D: lock flag
            *(char*)((int)g_pSkyVertexAlloc + 0x1D) = 1;
            pVertexData = (float*)(g_pSkyVertexAlloc[4]);  // +0x10: data pointer
        }
        else
        {
            // Use different lock path
            uint flags = 0;
            void* tempPtr = nullptr;
            if (*(char*)((int)g_pSkyVertexAlloc + 3) != '\0')
                flags = 0x3000;
            (**(code**)(*(int*)*g_pSkyVertexAlloc + 0x2c))((int*)*g_pSkyVertexAlloc, 0, 0, &tempPtr, flags);
            pVertexData = (float*)tempPtr;
        }

        // Lock index buffer
        if (*(char*)((int)g_pSkyIndexAlloc + 10) == '\0')
        {
            *(char*)((int)g_pSkyIndexAlloc + 0x29) = 1;
            pIndexData = (short*)(g_pSkyIndexAlloc[7]);  // +0x1C
        }
        else
        {
            uint flags = 0;
            if (*(char*)((int)g_pSkyIndexAlloc + 2) != '\0')
                flags = 0x3000;
            (**(code**)(*(int*)*g_pSkyIndexAlloc + 0x2c))((int*)*g_pSkyIndexAlloc, 0, 0, &g_pSkyIndexAlloc[5], flags);
            pIndexData = (short*)g_pSkyIndexAlloc[5];
        }

        // Build hemisphere vertices
        // Constants from globals
        float baseRadius = DAT_00e2b1a4;     // some radius
        float angleStep = DAT_00e447d4;      // 2pi/numRings? Actually used with uVar7 (0..9) so 10 steps
        float sectorStep = DAT_00e447e0;     // 2pi/numSectors? but multiplied by (uVar9 + baseRadius) => spherical?
        float radiusScale = DAT_00e2b1a4 / (fStack_c * ...);  // computed later

        // Initialize vertex data: first 6 floats? Actually pVertexData points to start of vertex array.
        // Each vertex: 3 floats (x,y,z). So stride = 12.
        // The vertex buffer starts with a center? Let's see: they set first 6 floats (2 vertices) to 0, then baseRadius? No, *puVar14 = 0; puVar14[1]=0; puVar14[2]=fVar3 (baseRadius); puVar14[3]=0; puVar14[4]=0; puVar14[5]=DAT_00e2eff4; so first two vertices: vertex0 = (0,0,baseRadius); vertex1 = (0,0,DAT_00e2eff4). That's likely the top and bottom poles of the dome.
        pVertexData[0] = 0.0f;
        pVertexData[1] = 0.0f;
        pVertexData[2] = baseRadius;
        pVertexData[3] = 0.0f;
        pVertexData[4] = 0.0f;
        pVertexData[5] = DAT_00e2eff4;  // some other radius for bottom? Actually might be for sky dome: pole at z = baseRadius, then bottom vertex z = other value.

        float* pVert = &pVertexData[6];
        // Now generate 10 rings x 7 sectors = 70 vertices
        for (uint ring = 0; ring < 10; ring++)
        {
            float theta = (float)(int)ring * angleStep;  // phi angle from top
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (uint sector = 0; sector < 7; sector++)
            {
                float phi = ((float)(int)sector + baseRadius) * sectorStep;  // baseRadius offset? that seems odd.
                float sinPhi = sin(phi); // actually not used? They compute cos(phi) later for z.
                // They computed: fStack_14 = (sector + baseRadius) * sectorStep
                // then call FUN_00b99fcb (probably sin/cos helper)
                float r = (sector + baseRadius) * sectorStep;  // this is really phi?
                float x = r * cosTheta;
                float y = r * sinTheta;
                float z = cos(phi);  // they compute cos of fStack_14, but fStack_14 is phi
                pVert[0] = x;
                pVert[1] = y;
                pVert[2] = z;
                pVert += 3;
            }
        }

        // Build index buffer (triangle strip for dome)
        short* pIdx = pIndexData;
        short baseIdx = 2;  // start after first two pole vertices? Actually indices reference vertices 0 and 1 are poles, then 2..71 are ring vertices.
        // They currently have sVar8 = 2; so first index written is 2? That matches.
        for (uint ring = 1; ring < 10; ring++)
        {
            uint nextRing = (ring < 9) ? ring + 1 : 0;  // they used uVar9 = uVar7 if >9 else 0; so if ring==9, nextRing=0 (wrap? but only 10 rings, so maybe last ring connects back to first? But they treat ring!=1 separately.
            // The loop iterates through sectors (0..6) and builds pairs of indices.
            // For ring==1, they skip writing a starting index? Actually they first write 0 for each ring? Code:
            // if (uVar7 != 1) { *psVar12 = 0; psVar12++; }  // This writes a degenerate index for non-first rings? Or strip restart?
            if (ring != 1)
            {
                *pIdx = 0;  // degenerate triangle? Or reset strip
                pIdx++;
            }
            *pIdx = 0;  // always write a 0? Actually they write *psVar12 = 0; then psVar12++;. So each ring begins with two zeros? That creates degenerate triangles.
            pIdx++;
            // Then for each sector, write two indices: current ring vertex (sector + baseIdx) and next ring vertex (sector + nextRing*7 + 2)
            for (uint sector = 0; sector < 7; sector++)
            {
                pIdx[0] = (short)(sector + baseIdx);
                pIdx[1] = (short)(sector + nextRing * 7 + 2);
                pIdx += 2;
            }
            // Then write a 1 (probably to end the strip)
            pIdx[0] = 1;
            pIdx += 1;
            // Then if ring < 9, write another 1 (another restart?)
            if (ring < 9)
            {
                pIdx[0] = 1;
                pIdx += 1;
            }
            baseIdx += 7;
        }

        // Unlock vertex buffer
        if (*(char*)((int)g_pSkyVertexAlloc + 7) == '\0')
            *(char*)((int)g_pSkyVertexAlloc + 0x1D) = 0;
        else
            (**(code**)(*(int*)*g_pSkyVertexAlloc + 0x30))((int*)*g_pSkyVertexAlloc);

        // Unlock index buffer
        if (*(char*)((int)g_pSkyIndexAlloc + 10) == '\0')
            *(char*)((int)g_pSkyIndexAlloc + 0x29) = 0;
        else
        {
            // Find min and max index to set bounds
            ushort minIdx = 0xFFFF;
            ushort maxIdx = 0;
            uint numIndices = (uint)g_pSkyIndexAlloc[3];  // +0x0C? Actually they use DAT_01205328[3] which is likely stored count.
            if (numIndices != 0)
            {
                for (uint i = 0; i < numIndices; i++)
                {
                    ushort idx = *(ushort*)(g_pSkyIndexAlloc[5] + i * 2);
                    if (idx < minIdx) minIdx = idx;
                    if (idx > maxIdx) maxIdx = idx;
                }
            }
            *(ushort*)((int)g_pSkyIndexAlloc + 0x10) = minIdx;  // +0x10: min index
            *(ushort*)((int)g_pSkyIndexAlloc + 0x12) = maxIdx;  // +0x12: max index
            (**(code**)(*(int*)*g_pSkyIndexAlloc + 0x30))((int*)*g_pSkyIndexAlloc);
        }

        // Store vertex count (0xb2 = 178)
        g_skyVertexCount = 0xb2;
        // Compute UV scale or something:
        float temp = DAT_00e447d8; // some constant
        // Call FUN_00b99e20? Could be sqrt? Actually they call FUN_00b99e20 twice? The decompile shows: dVar20 = DAT_00e447d8; FUN_00b99e20(); fStack_c = (float)dVar20; dVar20 = DAT_00e447c8; FUN_00b99e20(); then compute.
        // Possibly FUN_00b99e20 is sqrt? Then it computes scale = baseRadius / (sqrt(DAT_00e447d8)*sqrt(DAT_00e447c8)).
        // Without knowing, we'll just replicate.
        double d1 = DAT_00e447d8;
        FUN_00b99e20();  // assumed sqrt
        float sqrtD1 = (float)d1;
        double d2 = DAT_00e447c8;
        FUN_00b99e20();
        float sqrtD2 = (float)d2;
        g_skyTexCoordScale = baseRadius / (sqrtD1 * sqrtD2);
    }
}