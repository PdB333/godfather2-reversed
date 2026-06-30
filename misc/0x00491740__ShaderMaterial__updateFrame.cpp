// FUNC_NAME: ShaderMaterial::updateFrame
void __fastcall ShaderMaterial::updateFrame(int thisPtr)
// Function at 0x00491740: Per-frame update of shader constants, textures, and parameters.
// Called every frame to set dynamic rendering states based on global settings and local material data.
// 'thisPtr' points to a ShaderMaterial object with various offsets for shader resource handles,
// constant buffers, and texture indices.
{
    // Update view-projection matrix (assumed)
    updateViewProjection();

    // Update vertex shader constants from offset +0x1c0 (vertex constant buffer handle)
    // +0x14 is the D3D device pointer, +0x1d0 is the constant data structure
    if (*(int*)(thisPtr + 0x1c0) != 0) {
        setVertexShaderConstants(
            *(void**)(thisPtr + 0x14),                 // device
            *(int*)(thisPtr + 0x1c0),                   // shader constant buffer handle
            thisPtr + 0x1d0                             // constant data
        );
    }

    // Update lighting (assumed)
    updateLighting();

    // Commit/changed shader state (void function, no args)
    if (*(int*)(thisPtr + 0x2d0) != 0) {
        commitShaderState();
    }

    // Update pixel shader constants from offset +0x2d8
    if (*(int*)(thisPtr + 0x2d8) != 0) {
        setPixelShaderConstants(
            *(void**)(thisPtr + 0x14),
            *(int*)(thisPtr + 0x2d8),
            thisPtr + 0x2e0
        );
    }

    // Update additional vertex shader constants from offset +0x320 (800 in decimal)
    if (*(int*)(thisPtr + 0x320) != 0) {
        setVertexShaderConstants2(
            *(void**)(thisPtr + 0x14),
            *(int*)(thisPtr + 0x320),
            thisPtr + 0x330
        );
    }

    // Update pixel shader constants with a dynamic global value
    if (*(int*)(thisPtr + 0x344) != 0) {
        // Store global constant (likely screen width) into +0x348
        *(int*)(thisPtr + 0x348) = g_globalScreenWidth;
        commitShaderState();
    }

    // Update texture sampler with computed UV scales
    if (*(int*)(thisPtr + 0x34c) != 0) {
        // Retrieve texture info from global table indexed by value at +0x348
        // Each entry is 0x38 bytes; we need shorts at offset 2 and 4
        byte* textureInfo = nullptr;
        if (*(unsigned int*)(thisPtr + 0x348) < 0x1000) {
            textureInfo = &g_textureInfoTable[*(unsigned int*)(thisPtr + 0x348) * 0x38];
        }

        // Compute UV scale factors based on screen resolution and texture dimensions
        float uScale = g_screenHeight / (float)*(unsigned short*)(textureInfo + 2);
        float vScale = g_screenHeight / (float)*(unsigned short*)(textureInfo + 4);
        float texScale[2] = { uScale, vScale };
        setPixelShaderSampler(
            *(void**)(thisPtr + 0x14),
            *(int*)(thisPtr + 0x34c),
            texScale
        );
    }

    // Update another texture or shader resource with computed values
    if (*(int*)(thisPtr + 0x340) != 0) {
        float scaleVal = 0.0f;
        float param[4] = {0, 0, 0, 0};

        if (g_globalScaleFactor == 0.0f) {
            // If global scale is zero, set both to zero
            scaleVal = 0.0f;
            param[0] = 0.0f;
            param[1] = 0.0f;
        } else {
            // Compute scaling based on global factors
            float fVar = g_globalScaleFactor * g_anotherGlobal * g_sceneAmbient;
            float baseDiv = g_screenWidth / fVar;
            param[0] = baseDiv;
            param[1] = (fVar - g_anotherGlobal) * param[0];
        }

        // Extra dummy parameters (likely unused padding)
        param[2] = 0.0f;
        param[3] = 0.0f;

        setTexture(
            *(void**)(thisPtr + 0x14),
            *(int*)(thisPtr + 0x340),
            param
        );
    }
}

// Note: Called functions are named based on their presumed roles:
// updateViewProjection() – Fun_00490b20
// setVertexShaderConstants(void*, int, void*) – Fun_0060ad20
// updateLighting() – Fun_00492190
// commitShaderState() – Fun_006063b0 (void)
// setPixelShaderConstants(void*, int, void*) – Fun_0060b020
// setVertexShaderConstants2(void*, int, void*) – Fun_0060add0
// setPixelShaderSampler(void*, int, float*) – Fun_0060ac80
// setTexture(void*, int, float*) – Fun_0060add0 (reused for texture setting)
// Global constants:
// g_globalScreenWidth = DAT_0120535c
// g_textureInfoTable = DAT_011a0f28 (array of 0x38-byte structures)
// g_screenHeight = DAT_00e2cd54
// g_globalScaleFactor = DAT_0110b614
// g_anotherGlobal = DAT_011280f8
// g_sceneAmbient = DAT_00e2e780
// g_screenWidth = DAT_00e2b1a4