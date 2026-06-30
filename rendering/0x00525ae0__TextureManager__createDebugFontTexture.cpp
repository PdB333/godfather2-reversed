// FUNC_NAME: TextureManager::createDebugFontTexture
// Function address: 0x00525ae0
// Initializes a small font texture for debug UI overlay.
// Uses a singleton TextureManager to create a texture resource of size 0xa2e00 bytes
// with parameters (width=2, height=16, flags=0), then calls a setup function on the new texture.

void TextureManager::createDebugFontTexture(void)
{
    TextureManager* pMgr = getTextureManagerSingleton(); // FUN_009c8f80 - returns singleton pointer
    TextureCreateParams params;
    params.width = 2;    // local_c
    params.height = 16;  // local_8
    params.flags = 0;    // local_4

    // vtable call: first virtual function (index 0)
    // First argument: resource ID / size hint 0xa2e00
    // Second argument: pointer to TextureCreateParams struct
    int hTexture = pMgr->vtable->CreateTexture(0xa2e00, &params);

    if (hTexture != 0)
    {
        initializeTextureHandle(hTexture); // FUN_0051ee80 - e.g., load from memory, set defaults
    }
}