// FUNC_NAME: StreamManager::initStaticConfig
struct StreamConfig {
    void* basePtr;         // +0x00
    void* somePtr;         // +0x04
    unsigned int fileExt;  // +0x08 (ASCII "efe." little-endian)
    int version;           // +0x0c
    int channelCount;      // +0x10
    int flags1;            // +0x14
    unsigned int bufferSize;// +0x18 (2048)
    int flags2;            // +0x1c
    int flags3;            // +0x20
    int flags4;            // +0x24
};

static StreamConfig g_streamConfig; // DAT_01219050

StreamConfig* StreamManager::initStaticConfig() {
    g_streamConfig.flags1 = 0;
    g_streamConfig.flags2 = 0;
    g_streamConfig.flags3 = 0;
    g_streamConfig.flags4 = 0;
    g_streamConfig.somePtr = &PTR_LAB_00e379bc;
    g_streamConfig.fileExt = 0x2e656665; // "efe."
    g_streamConfig.version = 1;
    g_streamConfig.channelCount = 4;
    g_streamConfig.bufferSize = 0x800;
    g_streamConfig.basePtr = &PTR_LAB_00e37a18;
    return &g_streamConfig;
}