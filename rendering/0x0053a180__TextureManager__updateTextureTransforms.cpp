// FUNC_NAME: TextureManager::updateTextureTransforms
void __fastcall TextureManager::updateTextureTransforms(uint textureId1, uint textureId2)
{
    g_activeTextureId1 = in_EAX; // in_EAX is the value of EAX register, likely same as textureId1? Actually param_1 is passed in ECX, but here it uses in_EAX; maybe the function is __fastcall with first param in ECX, but the decompiler shows in_EAX as an alias for a register that holds the return of something? However, the input param textureId1 is clearly the first argument (param_1). We'll assume it's the same.
    g_activeTextureId2 = textureId2;

    // Check if we are in the correct rendering state (e.g., a specific shader or render target)
    if (g_currentState == &g_expectedStatePtr && g_stateTextureList == g_textureList)
    {
        // Release old textures if flags indicate they are loaded
        if (g_textureFlag1 != 0)
        {
            releaseTexture(); // FUN_006063b0
        }
        if (g_textureFlag2 != 0)
        {
            releaseTexture(); // FUN_006063b0
        }
        if (g_textureFlag3 != 0)
        {
            // Get texture info for first texture ID
            TextureInfo* texInfoPtr1 = nullptr;
            if (textureId1 < 0x1000)
            {
                texInfoPtr1 = &g_textureInfoArray[textureId1]; // stride 0x38 = sizeof(TextureInfo)
            }
            // Compute inverse width and height for first texture
            float invWidth1 = g_screenWidthDivisor / (float)(texInfoPtr1->width);  // width at offset +2
            float invHeight1 = g_screenWidthDivisor / (float)(texInfoPtr1->height); // height at offset +4

            // Get texture info for second texture ID
            TextureInfo* texInfoPtr2 = nullptr;
            if (textureId2 < 0x1000)
            {
                texInfoPtr2 = &g_textureInfoArray[textureId2];
            }
            float invWidth2 = g_screenWidthDivisor / (float)(texInfoPtr2->width);
            float invHeight2 = g_screenWidthDivisor / (float)(texInfoPtr2->height);

            // Pack UV transforms into a local array and apply them
            float uvTransforms[4] = { invWidth1, invHeight1, invWidth2, invHeight2 };
            applyUVTransform(g_textureList, g_textureFlag3, uvTransforms); // FUN_0060add0
        }
    }
}