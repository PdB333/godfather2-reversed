// FUNC_NAME: UISystem::renderTexture
void UISystem::renderTexture(void)
{
    uint textureIndex = in_EAX;
    g_currentTextureIndex = textureIndex;
    if ((g_singletonPointer == &g_singletonInstance) && (g_renderTarget == g_defaultRenderTarget))
    {
        if (g_clearFlag != 0)
        {
            clearRenderTarget();
        }
        if (g_spriteObject != 0)
        {
            D3DXVECTOR2 zeroVector;
            zeroVector.x = 0.0f;
            zeroVector.y = 0.0f;
            const TextureInfo* texInfo;
            if (textureIndex < 0x1000)
            {
                texInfo = &g_textureInfoArray[textureIndex];
            }
            else
            {
                texInfo = nullptr;
            }
            float scaleX = g_referenceScreenWidth / (float)texInfo->width;          // +0x02 (ushort)
            float scaleY = g_referenceScreenWidth / (float)texInfo->height;         // +0x04 (ushort)
            drawSprite(g_renderTarget, g_spriteObject, &zeroVector);
        }
    }
    return;
}