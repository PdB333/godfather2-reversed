// FUNC_NAME: ScreenCaptureManager::initializeStaticConfig
struct ScreenCaptureConfig {
    void* vtablePtr;               // +0x00, points to a static vtable pointer (PTR_LAB_00e37230)
    const char* formatName;        // +0x04, always "Screen"
    unsigned int formatMagic;      // +0x08, magic number 0x2e736372 (".scr"?)
    int field_0C;                  // +0x0C, initialized to 0
    int formatVariant;             // +0x10, initialized to 3
    int field_14;                  // +0x14, initialized to 0
    int bufferSize;                // +0x18, initialized to 0x800 (2048)
    int field_1C;                  // +0x1C, initialized to 0
    int field_20;                  // +0x20, initialized to 0
    int field_24;                  // +0x24, initialized to 0
};

// Global static instance, address matches the base address of the initialized data
static ScreenCaptureConfig g_screenCaptureConfig;

// External static table (vtable or function pointer array)
extern void* PTR_LAB_00e37230;

ScreenCaptureConfig* ScreenCaptureManager::initializeStaticConfig(void) {
    g_screenCaptureConfig.vtablePtr = &PTR_LAB_00e37230;
    g_screenCaptureConfig.formatName = "Screen";
    g_screenCaptureConfig.formatMagic = 0x2e736372;   // ".scr" if viewed as big-endian, but stored as integer
    g_screenCaptureConfig.field_0C = 0;
    g_screenCaptureConfig.formatVariant = 3;
    g_screenCaptureConfig.field_14 = 0;
    g_screenCaptureConfig.bufferSize = 0x800; // 2048
    g_screenCaptureConfig.field_1C = 0;
    g_screenCaptureConfig.field_20 = 0;
    g_screenCaptureConfig.field_24 = 0;
    return &g_screenCaptureConfig;
}