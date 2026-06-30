// FUNC_NAME: GlobalStateManager::applyStateFromSource
struct SourceState {
    // Offset 0x00 - 0x0C: vector data (e.g., position, rotation axis)
    float data0;
    float data1;
    float data2;
    float data3;
    // Offset 0x10 - 0x1C: possibly more fields, not used here
    char pad_10[16];
    // Offset 0x20: flags/mask
    uint32_t flags;
};

// Global state storage
static float g_stateData[4];          // DAT_01197d70 - 0x01197d7c
static float g_defaultData[4];        // DAT_01197d80 - 0x01197d8c
static uint32_t g_stateFlags;         // DAT_01197d90

// External constants (from game data)
extern const float C_DEFAULT_A;  // DAT_00e2b118
extern const float C_DEFAULT_B;  // DAT_00e2b1a4
extern const float C_DEFAULT_C;  // DAT_00e446c4

void GlobalStateManager::applyStateFromSource(SourceState* source) {
    g_stateFlags |= source->flags;
    g_stateData[0] = source->data0;
    g_stateData[1] = source->data1;
    g_stateData[2] = source->data2;
    g_stateData[3] = source->data3;

    // If the "reset" flag is set (bit 28), apply default state
    if ((g_stateFlags & 0x10000000) != 0) {
        g_stateData[0] = 0.0f;
        g_stateData[1] = 0.0f;
        g_stateData[2] = 0.0f;
        g_stateData[3] = 0.0f;
        g_defaultData[0] = C_DEFAULT_A;
        g_defaultData[1] = C_DEFAULT_B;
        g_defaultData[2] = C_DEFAULT_C;
        g_defaultData[3] = C_DEFAULT_B;  // Same as index 1
        g_stateFlags = 0x10000000;
    }
}