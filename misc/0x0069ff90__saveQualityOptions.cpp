// FUNC_NAME: saveQualityOptions
void saveQualityOptions(char applyNow)
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    // Write the config type (e.g., "Custom", "Low", "High")
    setConfigString("QualityOptions.ConfigType", DAT_00e50bc4);

    // Write each quality option
    sprintf(buffer, "QualityOptions.%s", "Bloom");
    setConfigByte(buffer, DAT_00e50be4[0]);

    sprintf(buffer, "QualityOptions.%s", "HDR"); // or whatever PTR_DAT_00e50b98 is
    setConfigByte(buffer, DAT_00e50be4[1]);

    sprintf(buffer, "QualityOptions.%s", "SSAO"); // or whatever PTR_DAT_00e50b9c is
    setConfigByte(buffer, DAT_00e50be4[2]);

    sprintf(buffer, "QualityOptions.%s", "EdgeAA");
    setConfigByte(buffer, DAT_00e50be4[3]);

    sprintf(buffer, "QualityOptions.%s", "Anisotropic"); // or whatever PTR_DAT_00e50ba4 is
    setConfigByte(buffer, DAT_00e50be4[4]);

    sprintf(buffer, "QualityOptions.%s", "ManipColor");
    setConfigByte(buffer, DAT_00e50be4[5]);

    sprintf(buffer, "QualityOptions.%s", "ActorMotionBlur");
    setConfigByte(buffer, DAT_00e50be4[6]);

    sprintf(buffer, "QualityOptions.%s", "Flare");
    setConfigByte(buffer, DAT_00e50be4[7]);

    sprintf(buffer, "QualityOptions.%s", "ToneMapping");
    setConfigByte(buffer, DAT_00e50bec[0]);

    sprintf(buffer, "QualityOptions.%s", "Decals");
    setConfigByte(buffer, DAT_00e50bec[1]);

    sprintf(buffer, "QualityOptions.%s", "ShaderQuality");
    setConfigInt(buffer, *(int*)&DAT_00e50bec[4]); // 4-byte value

    sprintf(buffer, "QualityOptions.%s", "Shadows");
    setConfigInt(buffer, DAT_00e50bf4); // 4-byte value

    if (applyNow != 0) {
        applyQualitySettings(); // FUN_0069fec0
    }
}