// FUNC_NAME: readQualityOptions
// Address: 0x0069ff90
// Reads quality option values from config system and optionally applies them.
void readQualityOptions(bool applySettings)
{
    char keyBuffer[1024];
    memset(keyBuffer, 0, sizeof(keyBuffer));

    // Read config type string (e.g., "High", "Medium", "Low")
    readConfigString("QualityOptions.ConfigType", g_qualityConfigType);

    // Read each individual quality option as a boolean/integer
    sprintf(keyBuffer, "QualityOptions.%s", "Bloom");
    readConfigBool(keyBuffer, g_qualityOptions.bloom);

    sprintf(keyBuffer, "QualityOptions.%s", /* likely "MotionBlur" or similar, pointer at 0x00e50b98 */);
    readConfigBool(keyBuffer, g_qualityOptions.motionBlur);

    sprintf(keyBuffer, "QualityOptions.%s", /* pointer at 0x00e50b9c */);
    readConfigBool(keyBuffer, g_qualityOptions.unknown1);

    sprintf(keyBuffer, "QualityOptions.%s", "EdgeAA");
    readConfigBool(keyBuffer, g_qualityOptions.edgeAA);

    sprintf(keyBuffer, "QualityOptions.%s", /* pointer at 0x00e50ba4 */);
    readConfigBool(keyBuffer, g_qualityOptions.unknown2);

    sprintf(keyBuffer, "QualityOptions.%s", "ManipColor");
    readConfigBool(keyBuffer, g_qualityOptions.manipColor);

    sprintf(keyBuffer, "QualityOptions.%s", "ActorMotionBlur");
    readConfigBool(keyBuffer, g_qualityOptions.actorMotionBlur);

    sprintf(keyBuffer, "QualityOptions.%s", "Flare");
    readConfigBool(keyBuffer, g_qualityOptions.flare);

    sprintf(keyBuffer, "QualityOptions.%s", "ToneMapping");
    readConfigBool(keyBuffer, g_qualityOptions.toneMapping);

    sprintf(keyBuffer, "QualityOptions.%s", "Decals");
    readConfigBool(keyBuffer, g_qualityOptions.decals);

    sprintf(keyBuffer, "QualityOptions.%s", "ShaderQuality");
    readConfigString(keyBuffer, g_qualityOptions.shaderQuality);  // probably string or enum

    sprintf(keyBuffer, "QualityOptions.%s", "Shadows");
    readConfigString(keyBuffer, g_qualityOptions.shadows);

    if (applySettings)
    {
        applyQualitySettings();  // FUN_0069fec0
    }
}