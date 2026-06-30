// FUNC_NAME: GlobalManager::initializeDefaults

struct GlobalManager {
    float field_00; // +0x00
    float field_04; // +0x04
    float field_08; // +0x08
    int field_0C;   // +0x0C
    int field_10;   // +0x10
    int field_14;   // +0x14
    int field_18;   // +0x18
    float field_1C; // +0x1C
    float field_20; // +0x20
    float field_24; // +0x24
    float field_28; // +0x28
    int field_2C;   // +0x2C
    int field_30;   // +0x30
    int field_34;   // +0x34
    float field_38; // +0x38
    float field_3C; // +0x3C
    int field_40;   // +0x40
    int field_44;   // +0x44
    int field_50;   // +0x50
};

// Global instance
GlobalManager g_globalManager;

// External constants (likely floats or ints)
extern float DAT_00e39f98;
extern float DAT_00e2b1a4;
extern float DAT_00e445ac;

GlobalManager* initializeDefaults(void) {
    g_globalManager.field_20 = DAT_00e39f98;
    g_globalManager.field_24 = DAT_00e39f98;
    g_globalManager.field_40 = 0;
    g_globalManager.field_44 = 0;
    g_globalManager.field_10 = 0;
    g_globalManager.field_14 = 0;
    g_globalManager.field_18 = 0;
    g_globalManager.field_1C = DAT_00e2b1a4;
    g_globalManager.field_00 = DAT_00e2b1a4;
    g_globalManager.field_04 = DAT_00e2b1a4;
    g_globalManager.field_08 = DAT_00e2b1a4;
    g_globalManager.field_28 = DAT_00e445ac;
    g_globalManager.field_2C = 0;
    g_globalManager.field_30 = 0;
    g_globalManager.field_34 = 0;
    g_globalManager.field_38 = DAT_00e2b1a4;
    g_globalManager.field_3C = DAT_00e2b1a4;
    g_globalManager.field_0C = 0;
    g_globalManager.field_50 = 0;
    return &g_globalManager;
}