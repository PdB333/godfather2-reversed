// FUNC_NAME: GfxSprite::render
// Address: 0x005312d0
// Role: Renders a sprite using texture info from a global array if a render pending flag is set.
//        Uses an index stored at +0x16c to lookup width/height from a table of 0x38-byte entries.
//        After rendering, clears the global pending flag.

void __thiscall GfxSprite::render(GfxSprite *this)
{
    void *textureInfo;
    float width;
    float height;

    if (g_renderPending != 0) {
        // Index into texture info array (0x38 bytes per entry, max 0x1000 entries)
        if (*(uint *)((int)this + 0x16c) < 0x1000) {
            textureInfo = (void *)((int)&g_textureInfoArray + *(uint *)((int)this + 0x16c) * 0x38);
        } else {
            textureInfo = (void *)0x0;
        }
        // Extract width and height as floats from ushort fields at offsets +2 and +4
        width = (float)*(unsigned short *)((int)textureInfo + 2);
        height = (float)*(unsigned short *)((int)textureInfo + 4);
        // Call underlying render function with position 0,0, size, texture handle, and scalars 1.0,1.0
        FUN_004ef520(this, 0.0f, 0.0f, width, height,
                     (int *)&g_textureHandle,
                     g_renderFlags,
                     g_renderPending,
                     0,
                     0,
                     1.0f,
                     1.0f);
        g_renderPending = 0;
    }
}