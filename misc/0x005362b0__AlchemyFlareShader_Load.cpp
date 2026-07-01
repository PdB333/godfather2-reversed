// Xbox PDB: AlchemyFlareShader::Load
// FUNC_NAME: GlowEffectShader::initialize
void GlowEffectShader::initialize()
{
    // Create shader handles and load shaders
    m_glowShader = createShaderHandle();                                    // +0x10
    m_bloomShader = loadShaderFromName(&shaderNameBloom);                   // +0x14 (PTR_DAT_010be020)
    graphicsApiInit();                                                       // +0x164 = m_bloomShader (copy?)
    m_bloomShaderCopy = m_bloomShader;                                      // +0x164
    m_glowShaderCopy = m_glowShader;                                        // +0x160

    m_ditherShader = loadShaderFromName(&shaderNameDither);                 // +0x170 (PTR_DAT_010be030)
    m_depthShader = loadShaderFromName(&shaderNameDepth);                   // +0x16c (PTR_DAT_010be050)
    m_anotherShader = createShaderHandle();                                 // +0x168
    m_yetAnotherShader = createShaderHandle();                              // +0x180
    m_coronaShader = loadShaderFromName(&shaderNameCorona);                 // +0x184 (PTR_DAT_010be060)

    // Platform-dependent shader loading (DAT_0120575b indicates platform)
    bool isXbox = (DAT_0120575b == '\0');                                    // probably checks platform flag
    m_alternateShader1 = nullptr;                                           // +0x174
    m_alternateShader2 = nullptr;                                           // +0x178

    if (isXbox) {
        m_alternateShader1 = createShaderHandle();                          // +0x174
        m_alternateShader2 = createShaderHandle();                          // +0x178
    } else {
        // PC path
        m_alternateShader1 = createShaderHandle();                          // +0x174
        m_alternateShader2 = createShaderHandle();                          // +0x178
    }

    m_coronaShader2 = loadShaderFromName(&shaderNameCorona2);               // +0x17c (PTR_DAT_010be040)

    // Get shader parameters
    m_glowInfoHandle = getShaderParameterByName(m_glowShader, "gVFGlowInfo"); // +0x130
    m_glowInfoHandle2 = 0;                                                  // +0x134
    m_modulateSamplerHandle = 0;                                            // +0x148
    m_queryModulateAlphaHandle = 0;                                         // +0x15c

    if (m_alternateShader1 != nullptr) {
        m_glowInfoHandle2 = getShaderParameterByName(m_alternateShader1, "gVFGlowInfo"); // +0x134
        if (isXbox) {
            m_queryModulateAlphaHandle = getShaderParameterByName(m_alternateShader1, "queryModulateAlpha"); // +0x15c
        } else {
            m_modulateSamplerHandle = getShaderParameterByName(m_alternateShader1, "modulate_sampler_vs"); // +0x148
        }
    }

    m_screenColorVsHandle = 0;                                              // +0x12C (300)
    m_modulateByCoronaInfoVsHandle = 0;                                     // +0x138
    m_modulateSamplerVsHandle = 0;                                          // +0x144
    m_gModulateInfoHandle = 0;                                              // +0x154
    m_unknownHandle = 0;                                                    // +0x158

    if (m_alternateShader2 != nullptr) {
        m_screenColorVsHandle = getShaderParameterByName(m_alternateShader2, "screen_color_vs"); // +0x12C
        if (isXbox) {
            m_unknownHandle = getShaderParameterByName(m_alternateShader2, "queryModulateAlpha"); // +0x158
        } else {
            m_modulateByCoronaInfoVsHandle = getShaderParameterByName(m_alternateShader2, "modulate_by_corona_info_vs"); // +0x138
            m_modulateSamplerVsHandle = getShaderParameterByName(m_alternateShader2, "modulate_sampler_vs"); // +0x144
            m_gModulateInfoHandle = getShaderParameterByName(m_alternateShader2, "gModulateInfo"); // +0x154
        }
    }

    // Sampler handles from various shaders
    m_primarySamplerHandle = getShaderParameterByName(m_coronaShader2, "primary_sampler"); // +0x13c
    m_depthSamplerHandle = getShaderParameterByName(m_depthShader, "depth_sampler"); // +0x140
    m_ditherSamplerHandle = getShaderParameterByName(m_ditherShader, "dither_sampler"); // +0x14c
    m_ditheringControlHandle = getShaderParameterByName(m_ditherShader, "dithering_control"); // +0x150

    return;
}