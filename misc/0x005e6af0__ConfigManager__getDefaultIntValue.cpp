// FUNC_NAME: ConfigManager::getDefaultIntValue

// Function address: 0x005e6af0
// Purpose: Retrieves a numeric value from a global configuration store using a zero-initialized key.
// Likely returns a default integer stored under key {0, 0}.

#include <cstdint>

// Forward declarations for called functions
// These are internal to the ConfigManager module
void* ConfigManager_GetValue(void* manager, const ConfigKey* key);
uint32_t ConfigManager_ResolveInt(void* manager, uint32_t value);

// Global pointer to the configuration manager singleton (DAT_01223514)
extern void* g_configManager;

// Key structure for configuration lookups
struct ConfigKey {
    uint8_t keyType;   // +0x00
    uint32_t keyValue; // +0x04
};

uint32_t ConfigManager::getDefaultIntValue() {
    ConfigKey key = {};
    key.keyType = 0;
    key.keyValue = 0;

    void* valuePtr = ConfigManager_GetValue(g_configManager, &key);
    if (valuePtr != nullptr) {
        uint32_t rawValue = *static_cast<uint32_t*>(valuePtr); // Dereference the returned pointer
        return ConfigManager_ResolveInt(g_configManager, rawValue);
    }
    return 0;
}