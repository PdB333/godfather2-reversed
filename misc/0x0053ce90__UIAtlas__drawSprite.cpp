// FUNC_NAME: UIAtlas::drawSprite
void UIAtlas::drawSprite(uint spriteIndex)
{
    // Check if batching is enabled
    if (g_bBatchEnabled != 0) {
        beginRendering();
    }

    // Clamp index to maximum entries (0x1000 = 4096)
    SpriteEntry* pEntry;
    if (spriteIndex < 0x1000) {
        pEntry = &g_aSpriteEntries[spriteIndex];
    } else {
        pEntry = nullptr;
    }

    // Compute texture coordinates from sprite entry dimensions
    ushort width = pEntry->width;   // +0x2
    ushort height = pEntry->height; // +0x4
    float u = g_fTextureSize / (float)width;
    float v = g_fTextureSize / (float)height;

    // Build source rectangle (u1, v1, u2, v2) in texture space
    // The texture is assumed to be square; the rectangle is positioned at (u, v) with size (u, 1-v)
    // This pattern suggests a specific sprite layout (possible coordinates from a grid)
    float rect[4];
    rect[0] = u;
    rect[1] = v;
    rect[2] = u;          // x2 = x1 (width is same as x offset, possibly a side effect of atlas layout)
    rect[3] = g_fTextureVEnd - v; // bottom = (full height in UV) - top

    // Draw the primary sprite
    drawRect(g_pRenderDevice, g_pPrimaryTexture, rect);

    // If a highlight texture is available, draw it with a scaled rect
    if (g_pHighlightTexture != nullptr) {
        float scale = g_fHighlightScale;
        rect[2] = u * scale;          // scaled width
        rect[3] = v * scale;          // scaled height (keeping top-left same)
        drawRect(g_pRenderDevice, g_pHighlightTexture, rect);
    }
}