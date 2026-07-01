// Xbox PDB: EARS::Alchemy::TEffectCorona::TType::TType
// FUNC_NAME: CoronaSystem::createDefaultConfig
struct CoronaSystemConfig {
    void* vtable;               // +0x00
    const char* name;           // +0x04
    uint32_t fourCC;            // +0x08
    int32_t field_0C;           // +0x0C
    int32_t version;            // +0x10
    int32_t field_14;           // +0x14
    int32_t bufferSize;         // +0x18
    int32_t field_1C;           // +0x1C
    int32_t field_20;           // +0x20
    int32_t field_24;           // +0x24
};

static CoronaSystemConfig g_CoronaConfig;

CoronaSystemConfig* CoronaSystem::createDefaultConfig()
{
    g_CoronaConfig.field_0C = 0;
    g_CoronaConfig.field_14 = 0;
    g_CoronaConfig.field_1C = 0;
    g_CoronaConfig.field_20 = 0;
    g_CoronaConfig.field_24 = 0;
    g_CoronaConfig.name = "Corona";
    g_CoronaConfig.fourCC = 0x2e666c63; // ".clf" in little-endian, likely "Corona" file magic
    g_CoronaConfig.version = 3;
    g_CoronaConfig.bufferSize = 0x800; // 2048 bytes
    g_CoronaConfig.vtable = &PTR_LAB_00e37fa0; // pointer to internal vtable
    return &g_CoronaConfig;
}