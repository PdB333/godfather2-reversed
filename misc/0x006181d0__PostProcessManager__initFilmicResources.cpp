// FUNC_NAME: PostProcessManager::initFilmicResources
void PostProcessManager::initFilmicResources(void)
{
    // Retrieve handles to shader parameters/textures from the material/system at +0x14
    // +0x14: pointer to a shader/resource manager instance
    int* resourceMgr = *(int**)(this + 0x14);

    // Store the handle for "m_FilmicParams" (likely a set of float parameters) at +0xa4
    *(int*)(this + 0xa4) = FUN_0060a580(resourceMgr, "m_FilmicParams");

    // Store the handle for the LUT sampler at +0xa8
    *(int*)(this + 0xa8) = FUN_0060a580(resourceMgr, "g_FilmicLUTSampler");

    // Store the handle for the tone mapping texture at +0xac
    *(int*)(this + 0xac) = FUN_0060a580(resourceMgr, "g_ToneMappingTexture");
}