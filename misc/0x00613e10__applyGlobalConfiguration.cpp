// FUNC_NAME: applyGlobalConfiguration
void applyGlobalConfiguration(uint32_t *configData)
{
    uint32_t *globalConfig = (uint32_t *)0x011f69f0;
    for (int i = 0; i < 16; i++)
    {
        globalConfig[i] = configData[i];
    }
    FUN_00424470(); // Likely initializes something based on the config
    if ((DAT_011f7430 & 1) != 0)
    {
        FUN_00614ab0(); // Optional processing when flag bit0 set
    }
}