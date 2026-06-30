// Xbox PDB: EARS::Alchemy::TEffectLight::TType::TType
// FUNC_NAME: LightManager::getStaticData
// Address: 0x004ffa90
// Initializes and returns a pointer to a global LightStaticData structure.

struct LightStaticData {
    void* vtable;          // +0x00: pointer to vtable or function table
    const char* name;      // +0x04: "Light"
    uint32_t typeId;       // +0x08: 0x2e6c6974 (likely a four-character code)
    uint32_t field_0C;     // +0x0C: zero
    uint32_t count;        // +0x10: 9
    uint32_t field_14;     // +0x14: zero
    uint32_t flags;        // +0x18: 0x800 (2048)
    uint32_t field_1C;     // +0x1C: zero
    uint32_t field_20;     // +0x20: zero
    uint32_t field_24;     // +0x24: zero
};

// Global instance at address 0x012190a0
LightStaticData g_lightStaticData;

LightStaticData* LightManager::getStaticData() {
    g_lightStaticData.vtable = &PTR_LAB_00e37bb8;
    g_lightStaticData.name = "Light";
    g_lightStaticData.typeId = 0x2e6c6974;
    g_lightStaticData.field_0C = 0;
    g_lightStaticData.count = 9;
    g_lightStaticData.field_14 = 0;
    g_lightStaticData.flags = 0x800;
    g_lightStaticData.field_1C = 0;
    g_lightStaticData.field_20 = 0;
    g_lightStaticData.field_24 = 0;
    return &g_lightStaticData;
}