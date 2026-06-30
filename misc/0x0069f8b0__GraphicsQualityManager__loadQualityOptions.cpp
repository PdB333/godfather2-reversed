// FUNC_NAME: GraphicsQualityManager::loadQualityOptions

void GraphicsQualityManager::loadQualityOptions(bool applyToRuntime)
{
    // Buffer for constructing key strings like "QualityOptions.Bloom"
    char keyBuffer[1024];
    keyBuffer[0] = '\0';
    memset(keyBuffer, 0, sizeof(keyBuffer));

    // Read the persisted quality config type; if not set, read default and save
    g_qualityConfigType = FUN_0069bcc0("QualityOptions.ConfigType", 0);
    if (g_qualityConfigType == 0) {
        g_qualityConfigType = FUN_0069f440();      // Default quality preset
        FUN_0069bf90("QualityOptions.ConfigType", g_qualityConfigType);
    }

    // --- Bitfield group 1 (8 boolean flags) ---
    // Flags are packed into 8 bytes at g_qualityFlags1 (0x00e50be4)
    sprintf(keyBuffer, "QualityOptions.%s", s_strBloom);            // "Bloom"
    g_qualityFlags1.bit0 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit0);

    sprintf(keyBuffer, "QualityOptions.%s", s_strUnknown1);          // PTR_DAT_00e50b98
    g_qualityFlags1.bit1 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit1);

    sprintf(keyBuffer, "QualityOptions.%s", s_strUnknown2);          // PTR_DAT_00e50b9c
    g_qualityFlags1.bit2 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit2);

    sprintf(keyBuffer, "QualityOptions.%s", s_strEdgeAA);            // "EdgeAA"
    g_qualityFlags1.bit3 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit3);

    sprintf(keyBuffer, "QualityOptions.%s", s_strUnknown3);          // PTR_DAT_00e50ba4
    g_qualityFlags1.bit4 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit4);

    sprintf(keyBuffer, "QualityOptions.%s", s_strManipColor);        // "ManipColor"
    g_qualityFlags1.bit5 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit5);

    sprintf(keyBuffer, "QualityOptions.%s", s_strActorMotionBlur);   // "ActorMotionBlur"
    g_qualityFlags1.bit6 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit6);

    sprintf(keyBuffer, "QualityOptions.%s", s_strFlare);             // "Flare"
    g_qualityFlags1.bit7 = FUN_0069bc30(keyBuffer, g_qualityFlags1.bit7);

    // --- Bitfield group 2 (partial) ---
    sprintf(keyBuffer, "QualityOptions.%s", s_strToneMapping);       // "ToneMapping"
    g_qualityFlags2.bit0 = FUN_0069bc30(keyBuffer, g_qualityFlags2.bit0);

    sprintf(keyBuffer, "QualityOptions.%s", s_strDecals);            // "Decals"
    g_qualityFlags2.bit1 = FUN_0069bc30(keyBuffer, g_qualityFlags2.bit1);

    // ShaderQuality is an enum, stored as 4 bytes (not a bool)
    sprintf(keyBuffer, "QualityOptions.%s", s_strShaderQuality);     // "ShaderQuality"
    g_qualityFlags2.shaderQuality = FUN_0069bcc0(keyBuffer, g_qualityFlags2.shaderQuality);

    // Shadows is also an enum, stored separately
    sprintf(keyBuffer, "QualityOptions.%s", s_strShadows);           // "Shadows"
    g_shadowQuality = FUN_0069bcc0(keyBuffer, g_shadowQuality);

    // If requested, apply the loaded options to the runtime quality flags
    if (applyToRuntime) {
        // Pack 8 byte flags from group1 into g_appliedFlags1 (0x00e50bd0)
        g_appliedFlags1.byte0 = g_qualityFlags1.bit0;
        g_appliedFlags1.byte1 = g_qualityFlags1.bit1;
        g_appliedFlags1.byte2 = g_qualityFlags1.bit2;
        g_appliedFlags1.byte3 = g_qualityFlags1.bit3;
        g_appliedFlags1.byte4 = g_qualityFlags1.bit4;
        g_appliedFlags1.byte5 = g_qualityFlags1.bit5;
        g_appliedFlags1.byte6 = g_qualityFlags1.bit6;
        g_appliedFlags1.byte7 = g_qualityFlags1.bit7;

        // Pack group2: first two bytes, then 4-byte shader quality
        g_appliedFlags2.byte0 = g_qualityFlags2.bit0;
        g_appliedFlags2.byte1 = g_qualityFlags2.bit1;
        g_appliedFlags2.shaderQuality = g_qualityFlags2.shaderQuality;  // 4 bytes

        // Copy the config type and shadow quality
        g_appliedConfigType = g_qualityConfigType;
        g_appliedShadowQuality = g_shadowQuality;
    }
}