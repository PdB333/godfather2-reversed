// FUNC_NAME: InitializeGlobalConfig
void InitializeGlobalConfig(void)
{
    // Call some base initialization (likely for subsystems)
    SomeBaseInitFunction();

    // Setup local configuration structure initialized from a global pointer
    ConfigurationData configData; // +0x00: pointer/data field, +0x04: int field, +0x08: byte field
    configData.field0 = g_pGlobalConfigPointer;  // DAT_01130470
    configData.field4 = 0;
    configData.field8 = 0;

    // Apply configuration (second parameter is likely a flag or context, 0 = default)
    ApplyConfiguration(&configData, 0);
}