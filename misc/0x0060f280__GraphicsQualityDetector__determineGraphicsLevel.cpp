// FUNC_NAME: GraphicsQualityDetector::determineGraphicsLevel
void GraphicsQualityDetector::determineGraphicsLevel(uint adapterIndex) // parameter param_1 -> adapterIndex
{
    int *pD3D;

    // If we already have a forced vendor ID, use that to set graphics level directly
    if (g_hardwareVendorId != -1) {
        g_graphicsLevel = g_hardwareVendorId;
        return;
    }

    // Create Direct3D9 object if not already created
    if (g_pD3D == nullptr) {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION); // D3D_SDK_VERSION = 0x20
    }

    pD3D = g_pD3D;

    // Call IDirect3D9::CheckDeviceFormat with unknown parameters (possibly for testing a specific format)
    // First call: likely to check if the format is supported on the default adapter
    (**(code **)(*g_pD3D + 0x28))(g_pD3D, adapterIndex, 1); // CheckDeviceFormat (vtable offset 0x28)
    int result1 = (**(code **)(*pD3D + 0x28))(pD3D, adapterIndex); // ??? This seems off: same offset but different signature
    if (result1 < 0) {
        g_graphicsLevel = 1; // Low quality fallback
        return;
    }

    // Second set of checks: three more calls (might be for different formats or device types)
    (**(code **)(*pD3D + 0x28))(pD3D, adapterIndex, 1);
    int result2 = (**(code **)(*pD3D + 0x28))(pD3D, adapterIndex, 1);
    int result3 = (**(code **)(*pD3D + 0x28))(pD3D, adapterIndex, 1);

    if (result2 < 0) {
        g_graphicsLevel = 1; // Low quality
        return;
    }

    if (result3 < 0) {
        g_graphicsLevel = 2; // Medium quality
        return;
    }

    // If all tests pass, use the value from uninitialized register (likely originally from hardware detection)
    g_graphicsLevel = unaff_EDI; // Store result (0 for high quality, or other threshold)
}

// Global variables (declared elsewhere)
int g_hardwareVendorId = -1; // +0x00f15a18
int g_graphicsLevel = 0; // +0x00f15a14
int *g_pD3D = nullptr; // +0x012058cc