// FUNC_NAME: ConfigManager::checkFeatureAndToggle

// Reconstructed from Ghidra at 0x007898c0
// Likely checks a feature flag (hashed) and toggles something via global manager.

class ConfigManager {
public:
    // Virtual interface for feature queries (vtable at *(this+0x0c))
    struct IFeatureInterface {
        // Method at vtable offset 0x10: checks if a feature identified by hash is enabled.
        // Returns bool (char) and optionally writes feature value to outValue.
        virtual char isFeatureEnabled(unsigned int featureHash, int* outValue) = 0; // +0x10
    };

    // +0x0c: pointer to feature interface
    IFeatureInterface* m_featureInterface;

    // Method at this+?
    void checkFeatureAndToggle();
};

// Global pointer (DAT_01131018) – likely a game manager singleton.
extern void* g_someGlobal; // DAT_01131018

// Helper functions (original names unknown)
int isGlobalManagerReady(void* manager); // FUN_0043b870
void resetFeatureState(int zero);        // FUN_009ae900

void __thiscall ConfigManager::checkFeatureAndToggle(ConfigManager* this) {
    int outValue = 0;
    // feature identifier hash (possibly for a runtime toggle)
    const unsigned int featureHash = 0x36cac259;

    char isEnabled = this->m_featureInterface->isFeatureEnabled(featureHash, &outValue);
    if (isEnabled) {
        // If feature is active, verify the global manager exists
        int ready = isGlobalManagerReady(g_someGlobal);
        if (ready != 0) {
            // Reset/disable the feature (0 argument likely means off)
            resetFeatureState(0);
        }
    }
}