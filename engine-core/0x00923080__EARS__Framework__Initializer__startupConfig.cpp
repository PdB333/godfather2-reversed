// FUNC_NAME: EARS::Framework::Initializer::startupConfig
void EARS::Framework::Initializer::startupConfig()
{
    // Temporary structure for config data: pointer to global data + two zero fields
    struct ConfigEntry {
        void* globalData;  // +0x00
        int32_t field04;   // +0x04
        uint8_t field08;   // +0x08 (likely followed by padding)
    };

    ConfigEntry entry;
    entry.globalData = (void*)DAT_011303f0;  // Reference to a global object
    entry.field04 = 0;
    entry.field08 = 0;

    // Register/config step – likely creates or initializes a manager component
    FUN_00408a00(&entry, 0);
}