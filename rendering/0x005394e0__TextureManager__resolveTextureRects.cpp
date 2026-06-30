// FUNC_NAME: TextureManager::resolveTextureRects
void __fastcall TextureManager::resolveTextureRects(uint textureId, uint secondaryTextureId)
{
    // Global state variables (from Ghidra DAT_...)
    extern int g_currentTextureId;       // DAT_0121b7e4
    extern int g_secondaryTextureId;     // DAT_0121b820
    extern void* g_currentRenderer;      // DAT_012058e8
    extern void* g_staticRenderer;       // &DAT_0121b740
    extern int g_rendererHandle;         // DAT_0121b754
    extern int RENDERER_2D;              // DAT_0121bbb0
    extern int RENDERER_3D;              // DAT_0121bbb4
    extern int g_flagA;                  // DAT_0121b9a0
    extern int g_handleA;                // DAT_0121b9a4
    extern int g_handleB;                // DAT_0121b9b8
    extern int g_handleC;                // DAT_0121b9bc
    extern int g_handleD;                // DAT_0121b9c4
    extern int g_handleE;                // DAT_0121b9c8
    extern float g_screenWidth;          // DAT_00e2cd54 (used as divisor for texture source rects)

    // Texture info array base and stride
    extern char g_textureInfoArray[0x1000 * 0x38]; // DAT_011a0f28 (max 4096 entries, 0x38 bytes each)
    const int MAX_TEXTURES = 0x1000;
    const int TEXTURE_INFO_STRIDE = 0x38;

    // Structure for source rectangle (position + size)
    struct Rect {
        int x;      // +0x00
        int y;      // +0x04
        float width;   // +0x08
        float height;  // +0x0C
    };

    // Store incoming arguments to globals (original behavior)
    g_currentTextureId = textureId;
    g_secondaryTextureId = secondaryTextureId;

    // Check if current renderer is the static 2D renderer instance
    if (g_currentRenderer == g_staticRenderer)
    {
        // Renderer type dispatch
        if (g_rendererHandle == RENDERER_2D)
        {
            // Flush any pending texture cache if flag is set
            if (g_flagA != 0)
            {
                flushTextureCache();
            }

            // Process primary texture source rectangle
            if (g_handleA != 0)
            {
                Rect rect = {0, 0, 0.0f, 0.0f};

                // Get texture info pointer (array lookup or null)
                char* texInfo = nullptr;
                if (g_currentTextureId < MAX_TEXTURES)
                {
                    texInfo = g_textureInfoArray + g_currentTextureId * TEXTURE_INFO_STRIDE;
                }

                // Compute source rect dimensions from texture metadata (ushort at offsets 2 and 4)
                rect.width = g_screenWidth / (float)(*(unsigned short*)(texInfo + 2));
                rect.height = g_screenWidth / (float)(*(unsigned short*)(texInfo + 4));

                // Apply rectangle to renderer
                applyTextureRect(g_rendererHandle, g_handleA, &rect);
            }
        }
        else if (g_rendererHandle == RENDERER_3D)
        {
            // Set base texture rectangle
            setTextureRect(g_rendererHandle, g_handleB);

            // Set additional rectangle if handleC is valid (uses secondary texture ID)
            if (g_handleC != 0)
            {
                setTextureRect(g_rendererHandle, g_handleC, secondaryTextureId);
            }

            // Process handleD texture source
            if (g_handleD != 0)
            {
                // Get texture info (returns 64-bit: low = pointer, high = some ID)
                uint64_t texInfo = getTextureInfo(g_currentTextureId);
                char* ptr = (char*)(int)texInfo;               // low 32 bits as pointer
                int id = (int)(texInfo >> 32);                 // high 32 bits as ID

                Rect rect = {0, 0, 0.0f, 0.0f};
                rect.width = g_screenWidth / (float)(*(unsigned short*)(ptr + 2));
                rect.height = g_screenWidth / (float)(*(unsigned short*)(ptr + 4));
                applyTextureRect(g_rendererHandle, id, &rect);
            }

            // Process handleE texture source (uses secondary texture ID)
            if (g_handleE != 0)
            {
                uint64_t texInfo = getTextureInfo(secondaryTextureId);
                char* ptr = (char*)(int)texInfo;
                int id = (int)(texInfo >> 32);

                Rect rect = {0, 0, 0.0f, 0.0f};
                rect.width = g_screenWidth / (float)(*(unsigned short*)(ptr + 2));
                rect.height = g_screenWidth / (float)(*(unsigned short*)(ptr + 4));
                applyTextureRect(g_rendererHandle, id, &rect);
            }
        }
    }
    return;
}