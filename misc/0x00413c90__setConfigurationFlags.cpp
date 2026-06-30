// FUNC_NAME: setConfigurationFlags
void setConfigurationFlags(void)
{
    // Enable XInput/controller related flags (bits 0,2,4,5)
    DAT_01205323 |= 0x35;
    // Set initialization done flag
    DAT_01205322 = 1;
    return;
}