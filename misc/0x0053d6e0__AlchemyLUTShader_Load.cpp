// Xbox PDB: AlchemyLUTShader::Load
// FUNC_NAME: PostEffectManager::initializeShaders
void __fastcall PostEffectManager::initializeShaders(int this)
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    uint *puVar5;
    uint uVar6;
    uint *puVar7;
    int *local_14;
    int local_10;
    
    // Initialize base system
    FUN_006127d0();
    
    // Get the main shader effect
    uVar2 = FUN_0060a380();
    *(uint *)(this + 0x10) = uVar2;  // +0x10: mainEffect
    
    // Process 55 post-processing effects (0x37 = 55)
    local_14 = &DAT_011283b0;  // Array of effect IDs
    puVar7 = &DAT_01198ee8;   // Array of effect data structures (0x1b * 4 = 108 bytes each)
    local_10 = 0x37;
    
    do {
        iVar1 = *local_14;  // Current effect ID
        *puVar7 = 0;        // Initialize flags to 0
        
        if (iVar1 != 0) {
            // Get the effect's shader program
            uVar3 = FUN_0060a2e0(iVar1);
            puVar7[-0x1a] = uVar3;  // +0x00: shaderProgram
            
            uVar6 = 0x100;  // Bit flag for first texture
            puVar5 = puVar7 + -0x16;  // +0x10: textureHandles[0]
            uVar3 = 0;
            
            // Load 6 texture parameters (0x18 / 4 = 6)
            do {
                uVar4 = FUN_0060a580(puVar7[-0x1a],
                                     *(undefined4 *)((int)&PTR_s_gLUTTexture1_010beb44 + uVar3));
                *puVar5 = uVar4;  // Store texture handle
                
                if (uVar4 != 0) {
                    *puVar7 = uVar6;  // Set flag bit for this texture
                }
                
                uVar3 = uVar3 + 4;
                puVar5 = puVar5 + 1;
                uVar6 = uVar6 + 0x100;  // Shift flag bit (0x100, 0x200, 0x400, etc.)
            } while (uVar3 < 0x18);
            
            // Load shader parameters
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bb_texture");
            puVar7[-0x19] = uVar3;  // +0x04: bbTexture
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "gLUT_params1");
            puVar7[-0x18] = uVar3;  // +0x08: gLUTParams1
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "gLUT_params2");
            puVar7[-0x17] = uVar3;  // +0x0C: gLUTParams2
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bloom_tintColor");
            puVar7[-0x10] = uVar3;  // +0x28: bloomTintColor
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bloom_blacktintColor");
            puVar7[-0xf] = uVar3;  // +0x2C: bloomBlackTintColor
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bloom_texture");
            puVar7[-0xe] = uVar3;  // +0x30: bloomTexture
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bloom_dcolor");
            puVar7[-0xd] = uVar3;  // +0x34: bloomDColor
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "bloom_blackcolor");
            puVar7[-0xc] = uVar3;  // +0x38: bloomBlackColor
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "g_TexelSize");
            puVar7[-0xb] = uVar3;  // +0x3C: gTexelSize
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "vignetteTexture");
            puVar7[-10] = uVar3;  // +0x40: vignetteTexture
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "depth_texture");
            puVar7[-9] = uVar3;  // +0x44: depthTexture
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "dof_params");
            puVar7[-8] = uVar3;  // +0x48: dofParams
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "blurTexture");
            puVar7[-7] = uVar3;  // +0x4C: blurTexture
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "dofFade");
            puVar7[-6] = uVar3;  // +0x50: dofFade
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "gLutBlueSlice");
            puVar7[-5] = uVar3;  // +0x54: gLutBlueSlice
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "saturateColor");
            puVar7[-4] = uVar3;  // +0x58: saturateColor
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "g_halfPixelOffset");
            puVar7[-3] = uVar3;  // +0x5C: gHalfPixelOffset
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "g_bloom_halfPixelOffset");
            puVar7[-2] = uVar3;  // +0x60: gBloomHalfPixelOffset
            
            uVar3 = FUN_0060a580(puVar7[-0x1a], "g_blur_halfPixelOffset");
            puVar7[-1] = uVar3;  // +0x64: gBlurHalfPixelOffset
            
            // Set feature flags based on available parameters
            if (puVar7[-0x10] != 0) {  // bloomTintColor exists
                *puVar7 = *puVar7 | 4;  // Flag: HAS_BLOOM_TINT
            }
            
            if ((puVar7[-0xc] == 0) && ((*puVar7 & 4) != 0)) {  // bloomBlackColor missing but bloomTint exists
                *puVar7 = *puVar7 | 8;  // Flag: USE_BLOOM_TINT_FOR_BLACK
            }
            
            if (puVar7[-0xb] != 0) {  // gTexelSize exists
                *puVar7 = *puVar7 | 0x10;  // Flag: HAS_TEXEL_SIZE
            }
            
            if (puVar7[-10] != 0) {  // vignetteTexture exists
                *puVar7 = *puVar7 | 1;  // Flag: HAS_VIGNETTE
            }
            
            if (puVar7[-8] != 0) {  // dofParams exists
                *puVar7 = *puVar7 | 0x20;  // Flag: HAS_DOF
            }
            
            if (puVar7[-5] != 0) {  // gLutBlueSlice exists
                *puVar7 = *puVar7 | 0x80;  // Flag: HAS_LUT_BLUE_SLICE
            }
            
            if (puVar7[-4] != 0) {  // saturateColor exists
                *puVar7 = *puVar7 | 2;  // Flag: HAS_SATURATE
            }
        }
        
        local_14 = local_14 + 1;
        puVar7 = puVar7 + 0x1b;  // Move to next effect structure (27 * 4 = 108 bytes)
        local_10 = local_10 + -1;
    } while (local_10 != 0);
    
    // Load vertex shader parameter for the main effect
    if (*(int *)(this + 0x10) != 0) {  // mainEffect exists
        uVar2 = FUN_0060a580(*(int *)(this + 0x10), "vPosScaleTranslationVS");
        *(uint *)(this + 0xac) = uVar2;  // +0xAC: vPosScaleTranslationVS
    }
    
    return;
}