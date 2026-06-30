// FUNC_NAME: renderFlashEffect

void renderFlashEffect(char shouldLoadNewTexture)
{
    unsigned int savedTexture2;
    unsigned int savedTexture1;
    unsigned int loadedTextureHandle;

    // Check if flash effect is globally enabled and we should load a new texture
    if ((shouldLoadNewTexture != '\0') && (gFlashEffectEnabled != '\0')) {
        // Load the flash overlay texture (resource ID 0x210098, type 6)
        loadedTextureHandle = loadResource(6, 0x210098, gArg3, gArg4, 1, 0xffffffff);
        gFlashTextureHandle = loadedTextureHandle;
    }

    savedTexture2 = gCurrentTexture2;
    savedTexture1 = gCurrentTexture1;  // Possibly two texture stages or previous state

    if (gFlashTextureHandle != 0) {
        // Save current texture states (push)
        gCurrentTexture2 = 0;
        gCurrentTexture1 = gFlashTextureHandle;

        // Set the flash texture stage
        setTexture(0, savedTexture1, savedTexture2);

        // Set viewport / scissor rect (full screen)
        setViewport(0, 0, 0, 1.0f, 1.0f);

        // Set color for additive blend pass 1 (white)
        setColor(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);

        // Enable additive blending
        enableBlend(1);

        // Set color for subtractive pass 2 (black with alpha)
        setColor(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

        // Disable blending for second pass? Actually disable
        disableBlend(1);

        // Restore previous texture states (pop)
        unsigned int restoreTexture2 = gCurrentTexture2;
        unsigned int restoreTexture1 = gCurrentTexture1;
        gCurrentTexture2 = 0;
        gCurrentTexture1 = savedTexture1;

        // Restore the texture
        setTexture(0, restoreTexture1, restoreTexture2);

        // Restore viewport
        setViewport(0, 0, 0, 1.0f, 1.0f);
    }
}