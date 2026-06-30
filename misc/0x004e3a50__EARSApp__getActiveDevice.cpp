// FUNC_NAME: EARSApp::getActiveDevice
// Function address: 0x004e3a50
// Returns a pointer to the active render device or a default handle.
// Uses global singleton pointer g_pApp (0x012054dc) and fallback g_hDefaultDevice (0x012058a8).
// The device handle is stored at offset 0x170 within the app object.

// Global state (defined elsewhere)
extern EARSApp* g_pApp;               // 0x012054dc
extern void* g_hDefaultDevice;        // 0x012058a8 - fallback handle

// Offset for the device handle within EARSApp
#define EARSApp_DeviceHandle_Offset 0x170

void* EARSApp::getActiveDevice()
{
    if (g_pApp != nullptr)
    {
        // Retrieve device handle from app object at offset 0x170
        return *(void**)((uint8_t*)g_pApp + EARSApp_DeviceHandle_Offset);
    }
    // Fallback to default device
    return g_hDefaultDevice;
}