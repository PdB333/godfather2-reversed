// FUNC_NAME: UIManager::setTextureScale
void __fastcall UIManager::setTextureScale(uint textureID1, uint textureID2) // textureID1 in ECX, textureID2 in EAX
{
    // Store IDs globally
    g_activeTextureID1 = textureID1;
    g_activeTextureID2 = textureID2;

    // Check if current UI screen is valid and matches expected pointers
    if (g_currentUIScreen == &g_expectedScreen1 && g_uiScreen == g_expectedScreen2) {
        // Close any existing image objects if they exist
        if (g_imageObjectA != nullptr) {
            closeImage(g_imageObjectA);
        }
        if (g_imageObjectB != nullptr) {
            closeImage(g_imageObjectB);
        }

        // Process first texture (from textureID1)
        if (g_imageObjectC != nullptr) {
            Vector2 position(0.0f, 0.0f);
            // Look up texture info from global database (max 4096 textures, each 0x38 bytes)
            TextureInfo* texInfo = nullptr;
            if (textureID1 < 0x1000) {
                texInfo = &g_textureDatabase[textureID1]; // offset +0x38 per entry
            }
            // Compute scale to fit base width (g_baseWidth)
            float scaleX = g_baseWidth / (float)texInfo->width;  // width at offset +2
            float scaleY = g_baseWidth / (float)texInfo->height; // height at offset +4
            // Position and scale stored in local struct
            Vector2 scale(scaleX, scaleY);
            setImageTransform(g_uiScreen, g_imageObjectC, &position, &scale);
        }

        // Process second texture (from textureID2) - same logic
        if (g_imageObjectD != nullptr) {
            Vector2 position(0.0f, 0.0f);
            TextureInfo* texInfo = nullptr;
            if (textureID2 < 0x1000) {
                texInfo = &g_textureDatabase[textureID2];
            }
            float scaleX = g_baseWidth / (float)texInfo->width;
            float scaleY = g_baseWidth / (float)texInfo->height;
            Vector2 scale(scaleX, scaleY);
            setImageTransform(g_uiScreen, g_imageObjectD, &position, &scale);
        }
    }
}