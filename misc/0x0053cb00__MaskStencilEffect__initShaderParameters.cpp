// FUNC_NAME: MaskStencilEffect::initShaderParameters
void __thiscall MaskStencilEffect::initShaderParameters() {
    extern void globalEffectSetup(); // FUN_006127d0
    extern int __fastcall loadMaterial(const char* name); // FUN_0060a2e0
    extern int __fastcall getParameterHandle(int material, const char* name); // FUN_0060a580

    globalEffectSetup();

    // Array of 7 material names for mask post-processing
    static const char* s_maskMaterialNames[] = {
        (const char*)0x1128394, // PTR_PTR_01128394 first element
        // ... (7 elements, defined elsewhere)
    };
    // End sentinel address 0x11283b0 marks array end

    // Halo color and parameter string tables (4 entries each)
    static const char* s_haloColorStrings[] = {
        "halo_color1", "halo_color2", "halo_color3", "halo_color4"
    };
    static const char* s_haloParamStrings[] = {
        "halo_param1", "halo_param2", "halo_param3", "halo_param4"
    };

    // Initialize mask structures
    for (int i = 0; i < 7; ++i) {
        MaskStructure& mask = m_maskStructures[i];
        int material = loadMaterial(s_maskMaterialNames[i]);
        mask.materialHandle = material;
        mask.maskTextureParam = getParameterHandle(material, "mask_texture");
        mask.halfPixelOffsetParam = getParameterHandle(material, "g_maskHalfPixelOffset");

        for (int j = 0; j < 4; ++j) {
            mask.haloColorParams[j] = getParameterHandle(material, s_haloColorStrings[j]);
            mask.haloParamParams[j] = getParameterHandle(material, s_haloParamStrings[j]);
        }
    }

    // Initialize stencil material
    int stencilMaterial = loadMaterial("stencil_texture_material"); // PTR_DAT_010be170
    m_stencilMaterialHandle = stencilMaterial;
    m_stencilTextureParam = getParameterHandle(stencilMaterial, "stencil_texture");
    m_stencil1OverSizeParam = getParameterHandle(stencilMaterial, "stencil_1oversize");
    m_stencilHalfPixelOffsetParam = getParameterHandle(stencilMaterial, "g_stencilHalfPixelOffset");
}

// Class structure (offsets from this):
// +0x00: ... (other members, not initialized here)
// +0xa4: m_maskStructures[7] (each 0x2C bytes)
//   +0x00: materialHandle (int)
//   +0x04: haloColorParams[4]
//   +0x14: haloParamParams[4]
//   +0x24: maskTextureParam
//   +0x28: halfPixelOffsetParam
// +0x1d8: m_stencilTextureParam
// +0x1dc: m_stencil1OverSizeParam
// +0x1e0: m_stencilHalfPixelOffsetParam
// +0x1e4: m_stencilMaterialHandle