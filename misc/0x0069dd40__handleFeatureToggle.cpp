// FUNC_NAME: handleFeatureToggle
// Function at 0x0069dd40: Toggles a feature based on global flags. If flag is set and counter is non-zero, disables feature then enables it.
// Global variables
extern bool g_bIsFeatureActive;  // DAT_0112a02b
extern int g_iFeatureCounter;    // DAT_0122337c

// External functions
extern void disableFeature(int param);  // FUN_004067e0
extern void enableFeature(int param);   // FUN_0040eaf0

undefined1 handleFeatureToggle(void)
{
    if (g_bIsFeatureActive && (g_iFeatureCounter != 0))
    {
        g_bIsFeatureActive = false;
        disableFeature(0);
    }
    enableFeature(1);
    return 1;
}