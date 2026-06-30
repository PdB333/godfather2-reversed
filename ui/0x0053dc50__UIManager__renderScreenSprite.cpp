// FUNC_NAME: UIManager::renderScreenSprite
// Address: 0x0053dc50
// Role: Renders a sprite for the current screen based on the given index

void UIManager::renderScreenSprite(uint spriteIndex) {
    // Global arrays (likely per-screen state)
    // DAT_0121bf30 = current screen index (0-based)
    // Each screen struct is 0x1b bytes
    uint8_t* screenVisibleFlags = (uint8_t*)0x01198eb0; // +0x00: visibility flag
    uint8_t* screenActiveFlags  = (uint8_t*)0x01198ee0; // +0x00: active flag

    // If screen is visible, call begin-render
    if (screenVisibleFlags[g_currentScreenIndex * 0x1b] != 0) {
        beginScreenRender(); // FUN_006063b0
    }

    // If screen is active, draw the sprite
    if (screenActiveFlags[g_currentScreenIndex * 0x1b] != 0) {
        // Sprite pool at 0x011a0f28, each entry 0x38 bytes, max 0x1000 entries
        struct Sprite {
            uint8_t  pad0[2];   // +0x00
            uint16_t width;     // +0x02
            uint16_t height;    // +0x04
            uint8_t  pad2[0x34]; // rest of 0x38 bytes
        };

        Sprite* sprite = nullptr;
        if (spriteIndex < 0x1000) {
            sprite = &((Sprite*)0x011a0f28)[spriteIndex];
        }

        // Rectangle for drawing (left, top, right, bottom)
        uint32_t rect[2] = {0, 0}; // local_20 (x/y?) and local_1c
        float scaleX = 0.0f, scaleY = 0.0f;

        if (sprite) {
            // DAT_00e2cd54 is likely screen height (or base resolution)
            scaleX = (float)g_screenHeight / (float)sprite->width;
            scaleY = (float)g_screenHeight / (float)sprite->height;
        }

        // Draw the scaled sprite
        drawScreenElement(g_renderContext, screenActiveFlags[g_currentScreenIndex * 0x1b], &rect);
    }
}