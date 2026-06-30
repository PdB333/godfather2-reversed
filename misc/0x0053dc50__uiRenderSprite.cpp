// FUNC_NAME: uiRenderSprite
void uiRenderSprite(void)
{
    // Global index used to look up sprite data (e.g., current UI screen or slot)
    extern int g_currentIndex; // DAT_0121bf30
    // Array of sprite resource metadata (size 0x1b per entry)
    extern uint8_t g_spriteFlags[]; // DAT_01198eb0
    // Array of sprite rendering data (size 0x1b per entry)
    extern uint8_t g_spriteData[]; // DAT_01198ee0
    // Render context pointer (device or canvas)
    extern void* g_renderContext; // DAT_0121be9c
    // Screen width constant (e.g., 640.0f)
    extern float g_screenWidth; // DAT_00e2cd54
    // Array of sprite resource entries (0x38 bytes each, up to 0x1000 indices)
    extern uint8_t g_spriteResources[]; // DAT_011a0f28

    // ESI register holds the sprite index passed implicitly (0..0xFFF)
    uint spriteIndex;
    __asm { mov spriteIndex, esi } // capture the register

    // Check first flag for this current index
    if (g_spriteFlags[g_currentIndex * 0x1b] != 0)
    {
        // Enable whatever resource/state is needed
        FUN_006063b0();
    }

    // Check second flag for this current index
    if (g_spriteData[g_currentIndex * 0x1b] != 0)
    {
        float renderData[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // pos x,y, scale x,y
        // Get sprite resource pointer; if out of range, null
        uint8_t* resourceEntry = (spriteIndex < 0x1000) ? &g_spriteResources[spriteIndex * 0x38] : nullptr;
        if (resourceEntry != nullptr)
        {
            // Compute scale factors from resource entry offsets +2 (width?) and +4 (height?)
            renderData[2] = g_screenWidth / (float)(*((uint16_t*)(resourceEntry + 2)));
            renderData[3] = g_screenWidth / (float)(*((uint16_t*)(resourceEntry + 4)));
        }
        // Render the sprite at (0,0) with computed scales
        FUN_0060add0(g_renderContext, &g_spriteData[g_currentIndex * 0x1b], &renderData);
    }
}