// FUNC_NAME: CWaterShaderManager::Initialize

// Function address: 0x0053c440
// Purpose: Initializes shader constant handles for water/particle effects.
// This function is likely a member of a graphics effect manager class that
// populates a table of shader parameter handles from preloaded shader resources.

void CWaterShaderManager::Initialize()
{
    // +0x10: Get the particle vertex shader resource (e.g., from a shader manager singleton)
    m_pParticleVS = static_cast<IShader*>(GetShaderResource());

    // +0x14: Get the particle pixel shader from a preloaded technique pointer
    // (PTR_DAT_010bde70 is a global pointer to a pixel shader technique)
    m_pParticlePS = static_cast<IShader*>(GetShaderFromPointer(&PTR_DAT_010bde70));

    // Initialize shared static shader resources (likely creates or retrieves common shaders)
    InitializeSharedShaders();

    // Store these shaders for global access (used by other rendering code)
    g_pParticleVS = m_pParticleVS;       // DAT_01198e48 = this+0x10
    g_pParticlePS = m_pParticlePS;       // DAT_01198e70 = this+0x14

    // Get additional shaders from static pointers and store them globally
    g_pWaterVS = GetShaderResource();                        // DAT_01198e74
    g_pWaterPS = GetShaderFromPointer(&PTR_DAT_010bdeb0);   // DAT_01198e54
    g_pWaterFX = GetShaderFromPointer(&PTR_DAT_010bdea0);   // DAT_01198e4c
    // ... (other global shader assignments omitted for brevity, but they follow the pattern)

    // --- Initialize particle shader constant handles ---
    // Array of 12 techniques pointed to by PTR_DAT_010bebd4
    // Each technique provides 3 constant handles: world_particle_pos3_alpha, ?, ?
    const IShader** particleTechniques = (const IShader**)&PTR_DAT_010bebd4; // array of 12 technique pointers
    ShaderConstantHandle* handlePtr = m_particleHandles; // +0xa8
    for (int i = 0; i < 12; i++)
    {
        const IShader* technique = particleTechniques[i];
        handlePtr[0] = technique->GetConstantHandle("world_particle_pos3_alpha");
        handlePtr[1] = technique->GetConstantHandle(PTR_LAB_00763274_3_00e38600); // unknown string constant
        handlePtr[2] = technique->GetConstantHandle(DAT_00e388d4);                // unknown string constant
        handlePtr += 3;
    }

    // --- Initialize water shader constant handles ---
    // Array of 13 techniques pointed to by PTR_DAT_010beba0
    // Each technique provides 8 constant handles for displacement mapping
    const IShader** waterTechniques = (const IShader**)&PTR_DAT_010beba0; // array of 13 technique pointers
    handlePtr = m_waterHandles; // +0xd0
    for (int i = 0; i < 13; i++)
    {
        const IShader* technique = waterTechniques[i];
        handlePtr[0] = technique->GetConstantHandle("texture_sampler");
        handlePtr[1] = technique->GetConstantHandle("texture_mask");
        handlePtr[2] = technique->GetConstantHandle("displacement_sampler");
        handlePtr[3] = technique->GetConstantHandle("colorMult_colorOffset_isCenter_lerpValue");
        handlePtr[4] = technique->GetConstantHandle("deltaUV_centerUV");
        handlePtr[5] = technique->GetConstantHandle("additivepass");
        handlePtr[6] = technique->GetConstantHandle("multiplypass");
        handlePtr[7] = technique->GetConstantHandle("scaling");
        handlePtr += 8;
    }

    // Get final vertex shader constant from the water vertex shader (g_pWaterVS)
    // +0x270: store handle for vertex position scaling/translation
    m_vPosScaleTranslationVS = g_pWaterVS->GetConstantHandle("vPosScaleTranslationVS");
}

// Note: The exact type names (IShader, ShaderConstantHandle) are guessed;
// they represent the underlying GPU shader objects and handle system.
// Global pointer arrays (PTR_DAT_010bebd4, PTR_DAT_010beba0) contain preloaded technique pointers.