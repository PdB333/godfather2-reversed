// Xbox PDB: SM_DeferredSpotLightClass::GetParamHandles
// FUNC_NAME: LightingShaderManager::initialize
void __thiscall LightingShaderManager::initialize()
{
    // Get resource manager from global pointer
    m_resourceManager = FUN_0060a2e0(PTR_DAT_01109efc);  // likely createResourceManager or getResourceManager
    // +0x14: resource manager pointer

    // Initialize shader program
    FUN_004907a0(); // likely loadShaderProgram or similar
    // +0x10: global shader program handle
    m_shaderProgram = DAT_01205458; // global shader program

    // Additional init
    FUN_00490a50(); // likely bindShaderConstants or prepareRenderState

    // Get shader parameter handles
    // Query parameter "g_lightDirection" from the resource manager
    m_lightDirectionHandle = FUN_0060a580(m_resourceManager, "g_lightDirection"); // +0x1c0
    // Query parameter "g_spotLightCoordScale" from the main shader program
    m_spotLightCoordScaleHandle = FUN_0060a580(m_shaderProgram, "g_spotLightCoordScale"); // +0x1e0
}