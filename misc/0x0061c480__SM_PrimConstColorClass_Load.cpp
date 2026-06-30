// Xbox PDB: SM_PrimConstColorClass::Load
// FUNC_NAME: MaterialManager::initialize
void __thiscall MaterialManager::initialize(void *this)
{
    uint32_t shaderHandle;
    uint32_t textureHandle;

    shaderHandle = getShaderManager();                                 // 0x0060a380
    *(uint32_t *)((int)this + 0x10) = shaderHandle;                   // store shader manager
    textureHandle = getTextureManager(&g_globalTextureManager);        // 0x0060a2e0, global pointer
    *(uint32_t *)((int)this + 0x14) = textureHandle;                  // store texture manager
    initRenderer();                                                    // 0x006127d0, global init
    *(uint32_t *)((int)this + 0xc0) = getFixedColorEffect(shaderHandle, "FixedColor"); // 0x0060a580
}