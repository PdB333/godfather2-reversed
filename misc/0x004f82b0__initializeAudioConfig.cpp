// FUNC_NAME: initializeAudioConfig
typedef struct {
    void* vtable;            // +0x00 pointer to function table
    void* dataPtr;           // +0x04 pointer to static config data
    uint32_t signature;      // +0x08 = 0x2e766665 (possibly "VFE." identifier)
    uint32_t flags;          // +0x0C = 1
    uint32_t field_0x10;     // +0x10 = 0
    uint32_t field_0x14;     // +0x14 = 0
    uint32_t bufferSize;     // +0x18 = 0x800 (2048 bytes)
    uint32_t field_0x1C;     // +0x1C = 0
    uint32_t field_0x20;     // +0x20 = 0
    uint32_t field_0x24;     // +0x24 = 0
} AudioConfig;

// Global audio configuration instance at 0x01219028
extern AudioConfig g_audioConfig;

void* initializeAudioConfig(void)
{
    g_audioConfig.field_0x10 = 0;
    g_audioConfig.field_0x14 = 0;
    g_audioConfig.field_0x1C = 0;
    g_audioConfig.field_0x20 = 0;
    g_audioConfig.field_0x24 = 0;
    g_audioConfig.dataPtr = &DAT_00e3792c;
    g_audioConfig.signature = 0x2e766665;
    g_audioConfig.flags = 1;
    g_audioConfig.bufferSize = 0x800;
    g_audioConfig.vtable = &PTR_LAB_00e37988;
    return &g_audioConfig;
}