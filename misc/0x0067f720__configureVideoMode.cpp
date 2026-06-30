// FUNC_NAME: configureVideoMode
// Function address: 0x0067f720 - Video mode configuration setup during initialization

#include <cstdint>

// Global video configuration structure pointer (offset +0x154 is a mode-change flag)
extern int* g_pVideoConfig; // DAT_0122339c

// Default video mode parameters (constants from global data)
extern int g_defaultVideoWidth;   // _DAT_00e50130
extern int g_defaultVideoHeight;  // _DAT_00e50134
extern int g_defaultVideoDepth;   // _DAT_00e50138
extern int g_defaultVideoFlags;   // _DAT_00e5013c

// Forward declarations of helper functions (reconstructed names)
void videoConfigInit();                                                   // FUN_00426000
void videoConfigSetDisplayMode(int modeIndex, int width, int height, int depth, int flags); // FUN_00426230
void videoConfigApplyDisplayMode(int modeIndex);                          // FUN_004262f0
void* getCurrentAdapterMode();                                            // FUN_004227a0
void* getModeInfo(void* adapterModeHandle);                               // FUN_00606370
void setTargetRefreshRate(short rateH, short rateV);                     // FUN_004e1dd0

void configureVideoMode()
{
    // Retrieve the video configuration pointer
    int* pConfig = g_pVideoConfig;

    // Initialize the video configuration subsystem
    videoConfigInit();

    // Set the "mode change pending" flag at offset +0x154
    *(int*)((char*)pConfig + 0x154) = 1;

    // Request display mode 0 with the default width, height, depth, and flags
    videoConfigSetDisplayMode(0, g_defaultVideoWidth, g_defaultVideoHeight, g_defaultVideoDepth, g_defaultVideoFlags);

    // Apply the requested display mode
    videoConfigApplyDisplayMode(0);

    // Obtain the current adapter mode (e.g., from DirectX)
    void* adapterMode = getCurrentAdapterMode();

    // Retrieve detailed mode information (structure with shorts at +2 and +4 likely indicating refresh rate)
    void* modeInfo = getModeInfo(adapterMode);

    // Extract the two refresh rate components
    short rateH = *(short*)((char*)modeInfo + 2);
    short rateV = *(short*)((char*)modeInfo + 4);

    // Set the target refresh rate for the display
    setTargetRefreshRate(rateH, rateV);
}