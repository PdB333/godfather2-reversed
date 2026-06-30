// FUNC_NAME: FeatureManager::setFeatureEnabled
// Address: 0x0069ea90
// Role: Sets a global feature flag and associated value. If the flag is false, calls a reset function.

// Global variables
extern char g_bFeatureEnabled;          // DAT_0112a064
extern uint32_t g_uDefaultFeatureValue; // _DAT_00d5cf70
extern uint32_t g_uFeatureValue;        // DAT_0112a068

// Forward declaration of the reset function
void resetFeature(); // FUN_0069e8b0

void setFeatureEnabled(char param_1)
{
    g_bFeatureEnabled = param_1;
    g_uFeatureValue = g_uDefaultFeatureValue;
    
    if (param_1 == '\0') {
        resetFeature();
    }
}