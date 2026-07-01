// FUNC_NAME: PostEffectManager::initFilmicParameters
void __thiscall PostEffectManager::initFilmicParameters(void) {
    // Retrieve effect system pointer from this+0x14
    int effectSystem = *(int *)(this + 0x14);
    // Look up shader parameter handles by name (function at 0x0060a580)
    int hFilmicParams = getParameterHandle(effectSystem, "m_FilmicParams");
    *(int *)(this + 0xa4) = hFilmicParams;
    int hFilmicLUTSampler = getParameterHandle(effectSystem, "g_FilmicLUTSampler");
    *(int *)(this + 0xa8) = hFilmicLUTSampler;
    int hToneMappingTexture = getParameterHandle(effectSystem, "g_ToneMappingTexture");
    *(int *)(this + 0xac) = hToneMappingTexture;
}