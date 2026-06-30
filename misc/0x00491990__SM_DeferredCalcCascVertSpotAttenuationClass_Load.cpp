// Xbox PDB: SM_DeferredCalcCascVertSpotAttenuationClass::Load
// FUNC_NAME: Shadow3rdManager::constructor

void __thiscall Shadow3rdManager::constructor(Shadow3rdManager* this)
{
    // +0x14: pointer to shader system / device context
    // +0x350: constant buffer handle for "g_3rdShadowSampler"
    // +0x354: constant buffer handle for "g_view_to_3rd_shadow"
    uint32_t* pShaderSystem;

    // Obtain shader system handle from a global singleton reference (PTR_DAT_0110a04c)
    pShaderSystem = GetShaderSystem(&g_pShaderSystemRef);
    *(uint32_t*)((uintptr_t)this + 0x14) = pShaderSystem;

    // Base class or subsystem initialization (likely sets up shadow rendering context)
    InitBaseShadow();
    // Additional initialization (e.g., shadow map resources)
    InitShadowResources();

    // Retrieve constant buffers by name from the shader system
    *(uint32_t*)((uintptr_t)this + 0x350) = GetShaderConstant(pShaderSystem, "g_3rdShadowSampler");
    *(uint32_t*)((uintptr_t)this + 0x354) = GetShaderConstant(pShaderSystem, "g_view_to_3rd_shadow");
}