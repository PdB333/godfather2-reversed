// FUNC_NAME: FontManager::createFontTable
FontTable* FontManager::createFontTable() {
    int iVar1;
    byte bVar2, bVar3, bVar4;
    float fVar5, fVar6, fVar7;
    FontTable *fontTable;
    uint uVar9;
    int iVar10, iVar12;
    uint uVar11;
    float fVar14;
    uint local_c[3] = {2, 0x10, 0};   // allocation parameters

    // Allocate font table struct (size 0x1368 = 4968 bytes)
    fontTable = (FontTable *)new(0x1368, &local_c);

    // Create a texture or surface (likely for font atlas)
    uVar9 = createTexture(9, 0x40, 0x80, 0x80, 1, 0xffffffff);
    iVar10 = setTextureParams(uVar9, 0x4000);
    if (iVar10 == -1) {
        releaseTexture(uVar9, 0);
        uVar9 = 0xffffffff;
    }

    // Set up internal pointers
    fontTable->glyphDataBase = &fontTable->glyphData;   // +0x103 *4 = 0x40c -> points to glyphData at offset 0x106*4=0x418
    fontTable->textureId = uVar9;                        // +0x104*4 = 0x410

    // Clear character mapping table (256 entries, each 4 bytes, at offset 8)
    for (iVar10 = 0; iVar10 < 0x100; iVar10++) {
        fontTable->charMap[iVar10] = 0;
    }

    // External raw font metrics (8 bytes per glyph, total 0x310 bytes = 98 glyphs)
    fontTable->rawMetrics = &rawFontData;   // DAT_00f112d8

    // Build mapping from character codes to glyph indices (first loop)
    for (uVar11 = 0, iVar10 = 0; uVar11 < 0xf50; uVar11 += 0x50, iVar10 += 0x10) {
        // rawMetrics structure might be something like (charCode, unknown, ...)
        int offset1 = iVar10 + (int)&rawFontData;   // Actually uses iVar10 offset into rawMetrics? Wait, the loop increments iVar10 by 0x10 and uVar11 by 0x50. Weird.
        // This part is hard to follow; likely setting up a map from character code to glyph slot.
        char c1 = *(char *) (rawFontData + iVar10);
        fontTable->charMap[c1] = &fontTable->glyphData + uVar11;   // like puVar8[*(byte *)(iVar10 + puVar8[0x102]) + 2] = puVar8[0x103] + uVar11
        char c2 = *(char *) (rawFontData + iVar10 + 8);
        fontTable->charMap[c2] = &fontTable->glyphData + uVar11 + 0x28;   // second character for the same glyph? Actually uses iVar1 = uVar11+0x28
    }

    // Build glyph rendering data from raw metrics (second loop)
    fVar7 = scaleFactor7;   // DAT_00f17664
    fVar6 = scaleFactor6;   // DAT_00e2dd1c
    fVar5 = scaleFactor5;   // DAT_00e2d7fc

    for (uVar11 = 0, iVar10 = 0; uVar11 < 0x310; uVar11 += 8, iVar10 += 0x28) {
        GlyphRenderData *renderData = &fontTable->glyphData[iVar10 / 0x28];   // each glyph takes 0x28 bytes
        uint8_t *raw = &rawFontData[uVar11];   // 8-byte entry

        // Store pointer back to raw metrics (optional)
        renderData->rawPointer = (uint32_ptr)(raw);   // at offset 0x24

        // Extract bytes
        fVar14 = (float)raw[4];
        float width = fVar14 * fVar6;
        float width2 = ((float)raw[3] + fVar14) * fVar6;
        float height = (float)raw[5] * fVar6;
        float height2 = ((float)raw[3 + 2? Actually raw[3] is used for width2 plus raw[5]??) 
        // Actually code: bVar2 = raw[5]; bVar3 = raw[2]; bVar4 = raw[3];
        renderData->u1 = fVar14 * fVar6;
        renderData->v1 = ((float)raw[3] + fVar14) * fVar6;
        renderData->u2 = (float)raw[5] * fVar6;
        renderData->v2 = ((float)raw[3] + (float)raw[5]) * fVar6; // wait raw[3] is used again? Actually bVar4 = raw[3]; so (bVar4 + bVar2)*fVar6
        renderData->xOffset = (float)(int)(char)raw[1] * fVar5;
        renderData->xAdvance = (float)(int)(char)raw[6] * fVar5;
        renderData->yOffset = (float)(int)(char)raw[7] * fVar7;
        renderData->width = (float)(uint8_t)raw[2] * fVar5;
        renderData->height = (float)(uint8_t)raw[3] * fVar7;
    }

    // Set some final value (likely reference to rendering context)
    fontTable->someReference = DAT_00e44978;   // at offset 0

    return fontTable;
}