// FUNC_NAME: TextureManager::createSmallTexture
void TextureManager::createSmallTexture(void)
{
    TextureManager* mgr = reinterpret_cast<TextureManager*>(FUN_009c8f80());
    // Texture creation parameters: width=2, height=16, flags=0
    struct {
        uint32_t width  = 2;   // +0x00
        uint32_t height = 0x10; // +0x04
        uint32_t flags  = 0;   // +0x08
    } params;
    int32_t textureHandle = mgr->vtable->createTexture(0xa2e00, &params);
    if (textureHandle != 0) {
        FUN_0051ee80(textureHandle);
    }
}