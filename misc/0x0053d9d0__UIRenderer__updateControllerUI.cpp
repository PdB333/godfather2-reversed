// FUNC_NAME: UIRenderer::updateControllerUI
// Function address: 0x0053d9d0
// Role: Updates UI scaling and rumble state based on per-player flags and resource dimensions.

// Global defines (from Ghidra analysis)
#define g_currentPlayerIndex (*(int*)0x0121bf30)          // Current player/controller index
#define g_playerRumbleFlags ((char*)0x01198e84)           // Array of per-player rumble flags (stride 0x1B)
#define g_playerScalingFlags ((char*)0x01198edc)          // Array of per-player scaling flags (stride 0x1B)
#define g_resourceArray ((char*)0x011a0f28)              // Array of resource structs (size 0x38 each, indexed by resource handle)
#define g_screenWidth (*(float*)0x00e2cd54)              // Screen width in pixels
#define g_uiManager (*(void**)0x0121be9c)                 // Pointer to UI manager/render target

// Forward declarations (from assumed engine functions)
extern void FUN_006063b0();  // Possibly stopRumble() or resetVibration()
extern void FUN_0060add0(void* uiManager, int scalingFlag, void* scaleVec); // Possibly setUIScale(scaleVec)

void UIRenderer::updateControllerUI() {
    // ESI likely holds a resource handle (e.g., texture index) stored as member variable
    // In the original decompile, unaff_ESI is used without initialization; we assume it's a member 'm_resourceHandle'
    uint resourceHandle = this->m_resourceHandle; // unaff_ESI

    // Check rumble flag for current player
    if (g_playerRumbleFlags[g_currentPlayerIndex * 0x1B] != 0) {
        FUN_006063b0(); // Reset or stop rumble effect
    }

    // Check scaling flag for current player
    if (g_playerScalingFlags[g_currentPlayerIndex * 0x1B] != 0) {
        char* pResource = nullptr;
        if (resourceHandle < 0x1000) {
            pResource = g_resourceArray + resourceHandle * 0x38;
        } else {
            pResource = nullptr; // Bounds check
        }

        // Compute scale factors from resource width/height at offsets +2 and +4
        float scaleX = g_screenWidth / (float)*(ushort*)(pResource + 2);
        if (resourceHandle < 0x1000) {
            pResource = g_resourceArray + resourceHandle * 0x38;
        } else {
            pResource = nullptr;
        }
        float scaleY = g_screenWidth / (float)*(ushort*)(pResource + 4);

        // Prepare zero-initialized vector (scale offset) and call UI update function
        float scaleVec[2] = { 0.0f, 0.0f }; // local_20, local_1c
        FUN_0060add0(g_uiManager, g_playerScalingFlags[g_currentPlayerIndex * 0x1B], scaleVec);
    }
}