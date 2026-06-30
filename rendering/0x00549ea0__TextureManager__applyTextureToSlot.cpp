// FUNC_NAME: TextureManager::applyTextureToSlot
void TextureManager::applyTextureToSlot(TextureSlot* slot, TextureHandle texture)
{
    // Clear the "valid" flag at offset 0x4 (e.g., byte field indicating slot is active)
    slot->field_4 = 0;

    // If a specific texture handle is provided, use it; otherwise fall back to the global default texture
    if (texture != 0) {
        this->m_pTextureSystem->assignTexture(slot, texture); // this->+0xC0 is a TextureSystem*
    } else {
        // Global reference: g_pGameManager (+0x24 points to a config struct, +0x6c holds default texture handle)
        TextureHandle defaultTex = *(TextureHandle*)(*(int*)(DAT_01223480 + 0x24) + 0x6c);
        this->m_pTextureSystem->assignTexture(slot, defaultTex);
    }
}