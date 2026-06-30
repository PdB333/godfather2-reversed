// FUNC_NAME: getScreenConfig

struct ScreenConfig {
    void* vtable;                 // +0x00: pointer to function table (PTR_LAB_00e37230)
    const char* screenName;       // +0x04: "Screen"
    uint32_t extensionMagic;      // +0x08: 0x2e736372 (".scr" reversed)
    uint32_t unknown0;            // +0x0C: 0
    int32_t width;                // +0x10: 3 (seems odd, maybe a mode index)
    int32_t unknown1;             // +0x14: 0
    int32_t height;               // +0x18: 0x800 (2048)
    int32_t unknown2;             // +0x1C: 0
    int32_t unknown3;             // +0x20: 0
    int32_t unknown4;             // +0x24: 0
};

// Static global instance
static ScreenConfig gScreenConfig;

// Returns a pointer to the global ScreenConfig after initializing it
ScreenConfig* getScreenConfig(void) {
    gScreenConfig.unknown0 = 0;
    gScreenConfig.unknown1 = 0;
    gScreenConfig.unknown2 = 0;
    gScreenConfig.unknown3 = 0;
    gScreenConfig.unknown4 = 0;
    gScreenConfig.screenName = "Screen";
    gScreenConfig.extensionMagic = 0x2e736372; // ".scr" in little-endian
    gScreenConfig.width = 3;      // likely a screen mode enum
    gScreenConfig.height = 0x800; // 2048 pixels
    gScreenConfig.vtable = reinterpret_cast<void*>(0x00e37230);  // PTR_LAB_00e37230
    return &gScreenConfig;
}