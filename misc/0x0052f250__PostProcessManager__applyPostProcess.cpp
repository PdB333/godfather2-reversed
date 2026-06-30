// FUNC_NAME: PostProcessManager::applyPostProcess
// Address: 0x0052f250
// Role: Applies post-processing effects (tone mapping, bloom, color grading, etc.) based on flags.
// param_1: unused (possibly this pointer)
// param_2: bitmask of effects to apply (bit0=release?, bit1=?, bit2=?, bit4=?, bit5=?, bits8-10=color grading)
// param_3: boolean indicating high quality mode (if non-zero and param_2 non-zero, enables additional pass)

void PostProcessManager::applyPostProcess(uint32_t thisPtr, uint32_t flags, int32_t highQuality)
{
    bool bHighQuality;
    int32_t renderSettingsChanged;
    int32_t renderMode;
    uint32_t uVar4;
    uint8_t* puVar5;
    uint32_t uVar6, uVar7;
    float vec4[4]; // local_30, local_2c, local_28, local_24

    // Check if render settings need updating
    renderSettingsChanged = DAT_01205540; // current render settings version?
    if (flags != DAT_01205538) { // expected flags?
        renderSettingsChanged = getCurrentRenderSettings(); // FUN_0053dff0
    }

    renderMode = DAT_01218e58; // current render mode (e.g., HDR, LDR)

    if (renderSettingsChanged != 0) {
        // Determine if high quality path should be used
        if ((highQuality == 0) || (bHighQuality = true, flags == 0)) {
            bHighQuality = false;
        }

        // If render mode matches and no override, set render target
        if ((DAT_011f38f0 == DAT_01218e58) && (DAT_011f38f4 == 0)) {
            setRenderTarget(1); // FUN_00609890
        } else {
            clearRenderTarget(DAT_011f38f0, DAT_01218e58); // FUN_0060df60
        }

        // Set initial post-process flags (tone mapping, bloom, etc.)
        DAT_0120551e = 1; // enable tone mapping?
        clampExposureMin(0x16); // DAT_012058d0 = max(0x16, DAT_012058d0)
        clampExposureMax(0x16); // DAT_00f15988 = min(0x16, DAT_00f15988)
        _DAT_011f3a30 = 1; // bloom flag?
        clampExposureMin(7);
        clampExposureMax(7);
        _DAT_011f39f4 = 0; // another flag
        clampExposureMin(0xe);
        clampExposureMax(0xe);
        _DAT_011f3a10 = 0;
        clampExposureMin(0x19);
        clampExposureMax(0x19);
        _DAT_011f3a3c = 5;
        clampExposureMin(0x18);
        clampExposureMax(0x18);
        _DAT_011f3a38 = 0;
        clampExposureMin(0xf);
        clampExposureMax(0xf);
        _DAT_011f3a14 = 0;
        clampExposureMin(0x1b);
        clampExposureMax(0x1b);
        _DAT_011f3a44 = 0;

        setRenderState(1, 2, 1); // FUN_00417cf0 (e.g., set blend mode)
        updateLUT(); // FUN_0053d950
        updateBloom(); // FUN_00612a60

        // Apply effects based on flags
        if ((flags >> 2 & 1) != 0) {
            // Effect: likely color grading or LUT application
            getCameraPosition(&vec4); // FUN_00514890
            setShaderConstant(&vec4); // FUN_0053dc00
            applyShader(); // FUN_0053dc50
            vec4[0] = DAT_01219200;
            vec4[1] = (float)DAT_01219204;
            vec4[2] = DAT_01219208;
            vec4[3] = DAT_01219224;
            if ((&DAT_01198eb4)[DAT_0121bf30 * 0x1b] != 0) {
                setShaderConstant(DAT_0121be9c, (&DAT_01198eb4)[DAT_0121bf30 * 0x1b], &vec4); // FUN_0060add0
            }
            vec4[0] = DAT_01219210;
            vec4[1] = DAT_01219214;
            vec4[2] = DAT_01219218;
            vec4[3] = DAT_01219228;
            if ((&DAT_01198eb8)[DAT_0121bf30 * 0x1b] != 0) {
                setShaderConstant(DAT_0121be9c, (&DAT_01198eb8)[DAT_0121bf30 * 0x1b], &vec4);
            }
            finishEffect(); // FUN_00515d70
        }

        if ((flags >> 4 & 1) == 0) {
            // Effect: standard tone mapping
            setRenderTarget(renderMode, (-(uint32_t)bHighQuality & 0xffef0000) + 0x210000); // FUN_00606e60
            renderSettingsChanged = DAT_012054dc; // texture handle?
        } else {
            // Effect: alternative tone mapping with texture lookup
            uVar4 = DAT_012058a4;
            if (DAT_012054dc != 0) {
                uVar4 = *(uint32_t*)(DAT_012054dc + 0x16c); // texture width/height?
            }
            if (uVar4 < 0x1000) {
                puVar5 = &DAT_011a0f28 + uVar4 * 0x38; // texture data array
            } else {
                puVar5 = nullptr;
            }
            vec4[0] = DAT_01197d74 / (float)*(uint16_t*)(puVar5 + 2); // width ratio
            uVar4 = DAT_012058a4;
            if (DAT_012054dc != 0) {
                uVar4 = *(uint32_t*)(DAT_012054dc + 0x16c);
            }
            if (uVar4 < 0x1000) {
                puVar5 = &DAT_011a0f28 + uVar4 * 0x38;
            } else {
                puVar5 = nullptr;
            }
            vec4[1] = DAT_01197d74 / (float)*(uint16_t*)(puVar5 + 4); // height ratio
            vec4[2] = DAT_01197d70;
            vec4[3] = DAT_01197d78;
            if ((&DAT_01198ebc)[DAT_0121bf30 * 0x1b] != 0) {
                setShaderConstant(DAT_0121be9c, (&DAT_01198ebc)[DAT_0121bf30 * 0x1b], &vec4);
            }
            renderSettingsChanged = DAT_012054dc;
            // Reset texture coordinates
            DAT_01197d70 = 0;
            DAT_01197d74 = 0.0f;
            DAT_01197d78 = 0;
            _DAT_01197d7c = 0;
            _DAT_01197d80 = DAT_00e2b118;
            _DAT_01197d84 = DAT_00e2b1a4;
            _DAT_01197d88 = DAT_00e446c4;
            _DAT_01197d8c = DAT_00e2b1a4;
            DAT_01197d90 = 0;
            setRenderTarget(renderMode, (-(uint32_t)bHighQuality & 0xfff00000) + 0x200000);
        }

        if ((flags & 1) != 0) {
            // Effect: release temporary texture
            releaseTexture(DAT_01125290); // FUN_0053de00
            DAT_01125290 = 0;
            renderSettingsChanged = DAT_012054dc;
        }

        if ((flags >> 5 & 1) != 0) {
            // Effect: full-screen pass (e.g., bloom composite)
            beginRender(); // FUN_00518510
            uVar7 = DAT_012058a8;
            uVar6 = DAT_012058a8;
            if (renderSettingsChanged != 0) {
                uVar6 = *(uint32_t*)(renderSettingsChanged + 0x170); // render target handle?
            }
            setRenderTarget(uVar6, 0x210000);
            setRenderTarget(*(uint32_t*)(&DAT_01218e88 + (-(uint32_t)(DAT_012192f0 != 0x4000000) & 10) * 8), 0x200000);
            if (renderSettingsChanged != 0) {
                uVar7 = *(uint32_t*)(renderSettingsChanged + 0x170);
            }
            setViewport(uVar7); // FUN_0053de70
            if ((&DAT_01198ec8)[DAT_0121bf30 * 0x1b] != 0) {
                setShaderConstant(DAT_0121be9c, (&DAT_01198ec8)[DAT_0121bf30 * 0x1b], local_20); // local_20 unused?
            }
            endRender(); // FUN_0053df00
            finishComposite(); // FUN_0053deb0
            finishBloom(); // FUN_00517f50
        }

        if ((flags & 0x700) != 0) {
            // Effect: color grading (bits 8-10)
            setColorGrading(&DAT_0121930c, DAT_01219344); // FUN_0053dac0
            applyColorGrading(); // FUN_0053db50
        }

        if ((flags >> 1 & 1) != 0) {
            // Effect: additional pass (e.g., vignette)
            applyVignette(); // FUN_0052a170
            if ((&DAT_01198ed8)[DAT_0121bf30 * 0x1b] != 0) {
                setShaderConstant(DAT_0121be9c, (&DAT_01198ed8)[DAT_0121bf30 * 0x1b], extraout_ECX); // extraout_ECX likely a vector
            }
        }

        // Finalize post-process
        finalizePostProcess(); // FUN_0053d9d0
        setRenderTarget(1); // FUN_00609810

        if (bHighQuality) {
            applyHighQualityPass(); // FUN_0052ae50
        } else {
            applyStandardPass(); // FUN_00528070
        }

        finalizeFrame(); // FUN_00612e00

        // Re-clamp exposure and set final flags
        clampExposureMin(0x16);
        clampExposureMax(0x16);
        _DAT_011f3a30 = 1;
        clampExposureMin(7);
        clampExposureMax(7);
        _DAT_011f39f4 = 1;
        clampExposureMin(0xe);
        clampExposureMax(0xe);
        _DAT_011f3a10 = 1;
        clampExposureMin(0x19);
        clampExposureMax(0x19);
        _DAT_011f3a3c = 7;
        clampExposureMin(0x18);
        clampExposureMax(0x18);
        _DAT_011f3a38 = 0;
        clampExposureMin(0xf);
        clampExposureMax(0xf);
        _DAT_011f3a14 = 0;
        clampExposureMin(0x1b);
        clampExposureMax(0x1b);
        _DAT_011f3a44 = 0;

        setRenderState(1, 5, 6); // final render state
    }
}