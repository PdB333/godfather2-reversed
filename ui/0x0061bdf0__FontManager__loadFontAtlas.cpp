// FUNC_NAME: FontManager::loadFontAtlas
// Address: 0x0061bdf0
// Initializes a font atlas structure from a loaded resource file.
// Allocates a block of 0x1368 bytes, sets up character glyph data and vertex buffers.

struct FontAtlas {
    float* vertexData; // +0x0: pointer to vertex buffer (float array)
    uint32_t unknown1; // +0x4: ?
    uint32_t* glyphTable; // +0x2: array of 256 pointers to glyph entries (each 4 bytes)
    uint32_t* glyphDataPtr; // +0x102: pointer to glyph metric table (byte array)
    uint32_t* vertexBufferPtr; // +0x103: pointer to vertex buffer (float array)
    uint32_t resourceHandle; // +0x104: handle to loaded resource
};

FontAtlas* FontManager::loadFontAtlas() {
    int iVar1;
    byte bVar2, bVar3, bVar4;
    float fVar5, fVar6, fVar7;
    FontAtlas* atlas;
    uint32_t uVar9;
    int iVar10;
    uint32_t uVar11;
    int iVar12;
    FontAtlas* puVar13;
    float fVar14;
    undefined4 local_c = 2;
    undefined4 local_8 = 0x10;
    undefined4 local_4 = 0;

    // Allocate memory for font atlas structure (size 0x1368)
    atlas = (FontAtlas*)(**(code**)*DAT_01205868)(0x1368, &local_c);

    // Load resource: type 9, flags 0x40, width 0x80, height 0x80, mipmaps 1, unknown -1
    uVar9 = FUN_00606c80(9, 0x40, 0x80, 0x80, 1, 0xffffffff);
    iVar10 = FUN_00606ac0(uVar9, 0x4000); // Open resource with size 0x4000
    if (iVar10 == -1) {
        FUN_006065a0(uVar9, 0); // Close resource
        uVar9 = 0xffffffff;
    }

    // Set vertex buffer pointer (self-referential)
    atlas->vertexBufferPtr = (uint32_t*)((uint32_t)atlas + 0x106);
    atlas->resourceHandle = uVar9;

    // Initialize glyph table (256 entries) to zero
    uVar11 = 0;
    puVar13 = (FontAtlas*)((uint32_t)atlas + 8); // offset +2
    for (iVar10 = 0x100; iVar10 != 0; iVar10--) {
        *puVar13 = 0;
        puVar13 = (FontAtlas*)((uint32_t)puVar13 + 4);
    }

    // Set glyph metric table pointer (global data)
    atlas->glyphDataPtr = &DAT_00f112d8;

    // First loop: build glyph lookup table from metric data
    iVar10 = 0;
    do {
        // Each glyph metric entry is 16 bytes? Actually using byte offsets
        // puVar8[0x102] is the base of metric table
        // puVar8[0x103] is the vertex buffer base
        // uVar11 is vertex buffer offset (0x50 per glyph? Actually 0x50 per pair)
        atlas->glyphTable[*(byte*)(iVar10 + (uint32_t)atlas->glyphDataPtr) + 2] = 
            (uint32_t)atlas->vertexBufferPtr + uVar11;
        iVar12 = iVar10 + 8;
        iVar1 = uVar11 + 0x28;
        uVar11 += 0x50;
        iVar10 += 0x10;
        atlas->glyphTable[*(byte*)(iVar12 + (uint32_t)atlas->glyphDataPtr) + 2] = 
            (uint32_t)atlas->vertexBufferPtr + iVar1;
        // These globals are scaling factors (probably texture size)
        fVar7 = DAT_00f17664;
        fVar6 = DAT_00e2dd1c;
        fVar5 = DAT_00e2d7fc;
    } while (uVar11 < 0xf50);

    // Second loop: fill vertex data for each glyph (98 entries, each 0x28 bytes)
    iVar10 = 0;
    uVar11 = 0;
    do {
        // Store pointer to metric table entry in vertex buffer
        *(uint32_t*)(iVar10 + 0x24 + (uint32_t)atlas->vertexBufferPtr) = 
            (uint32_t)atlas->glyphDataPtr + uVar11;
        iVar12 = (uint32_t)atlas->glyphDataPtr + uVar11;
        // Read byte data from metric table (8 bytes per entry)
        fVar14 = (float)*(byte*)((uint32_t)atlas->glyphDataPtr + 4 + uVar11);
        bVar2 = *(byte*)(iVar12 + 5);
        bVar3 = *(byte*)(iVar12 + 2);
        bVar4 = *(byte*)(iVar12 + 3);
        // Compute UV coordinates and positions
        *(float*)(iVar10 + 8 + (uint32_t)atlas->vertexBufferPtr) = fVar14 * fVar6;
        *(float*)(iVar10 + 0xc + (uint32_t)atlas->vertexBufferPtr) = ((float)bVar3 + fVar14) * fVar6;
        *(float*)(iVar10 + 0x10 + (uint32_t)atlas->vertexBufferPtr) = (float)bVar2 * fVar6;
        *(float*)(iVar10 + 0x14 + (uint32_t)atlas->vertexBufferPtr) = ((float)bVar4 + (float)bVar2) * fVar6;
        *(float*)(iVar10 + 0x18 + (uint32_t)atlas->vertexBufferPtr) = 
            (float)(int)*(char*)(uVar11 + 1 + (uint32_t)atlas->glyphDataPtr) * fVar5;
        *(float*)(iVar10 + 0x1c + (uint32_t)atlas->vertexBufferPtr) = 
            (float)(int)*(char*)(uVar11 + 6 + (uint32_t)atlas->glyphDataPtr) * fVar5;
        *(float*)(iVar10 + 0x20 + (uint32_t)atlas->vertexBufferPtr) = 
            (float)(int)*(char*)(uVar11 + 7 + (uint32_t)atlas->glyphDataPtr) * fVar7;
        *(float*)(iVar10 + (uint32_t)atlas->vertexBufferPtr) = 
            (float)*(byte*)(uVar11 + 2 + (uint32_t)atlas->glyphDataPtr) * fVar5;
        *(float*)(iVar10 + 4 + (uint32_t)atlas->vertexBufferPtr) = 
            (float)*(byte*)(uVar11 + 3 + (uint32_t)atlas->glyphDataPtr) * fVar7;
        uVar11 += 8;
        iVar10 += 0x28;
    } while (uVar11 < 0x310);

    // Store global vertex data pointer
    atlas->vertexData = (float*)DAT_00e44978;
    return atlas;
}