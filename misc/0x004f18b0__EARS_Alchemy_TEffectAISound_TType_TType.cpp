// Xbox PDB: EARS::Alchemy::TEffectAISound::TType::TType
// FUNC_NAME: AISoundConfig::initSingleton
// Address: 0x004f18b0 - Initializes global AI sound configuration singleton
// Returns pointer to the global AISoundConfig instance

struct AISoundConfig {
    void* vtable;          // +0x00
    const char* name;      // +0x04 - "AISound"
    uint32_t magic;        // +0x08 - 0x2e616973
    uint32_t field_0C;     // +0x0C - 1
    uint32_t field_10;     // +0x10 - 2
    uint32_t field_14;     // +0x14 - 0
    uint32_t maxSounds;    // +0x18 - 0x800 (2048)
    uint32_t field_1C;     // +0x1C - 0
    uint32_t field_20;     // +0x20 - 0
    uint32_t field_24;     // +0x24 - 0
};

// Global instance at 0x01218f34
static AISoundConfig g_AISoundConfig;

// Vtable pointer for AISoundConfig (at PTR_LAB_00e37518)
extern void* g_AISoundConfigVtable;

AISoundConfig* AISoundConfig::initSingleton()
{
    g_AISoundConfig.vtable = &g_AISoundConfigVtable;
    g_AISoundConfig.name = "AISound";
    g_AISoundConfig.magic = 0x2e616973;
    g_AISoundConfig.field_0C = 1;
    g_AISoundConfig.field_10 = 2;
    g_AISoundConfig.field_14 = 0;
    g_AISoundConfig.maxSounds = 0x800;
    g_AISoundConfig.field_1C = 0;
    g_AISoundConfig.field_20 = 0;
    g_AISoundConfig.field_24 = 0;
    return &g_AISoundConfig;
}