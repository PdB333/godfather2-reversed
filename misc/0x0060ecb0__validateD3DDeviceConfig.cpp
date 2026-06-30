// FUNC_NAME: validateD3DDeviceConfig

#include <d3d9.h>

// Global Direct3D9 object pointer
IDirect3D9* g_pD3D = nullptr;

// Function called via registers: ESI points to first config block, EDI points to second.
// Config blocks contain: [0] Adapter, [1] DeviceType, [3] low byte = bWindowed (for first)
// and [0] AdapterFormat, [1] BackBufferFormat (for second)
// Returns 9 on success, 4 on failure.
int validateD3DConfig(DWORD* pConfig1, DWORD* pConfig2)
{
    HRESULT hr;

    // Ensure D3D object exists
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (g_pD3D == nullptr)
            return 4;
    }

    // CheckDeviceType: verify hardware support for requested device type and formats
    hr = g_pD3D->CheckDeviceType(
        pConfig1[0],                     // Adapter (e.g., D3DADAPTER_DEFAULT)
        (D3DDEVTYPE)pConfig1[1],        // DeviceType (e.g., D3DDEVTYPE_HAL)
        (D3DFORMAT)pConfig2[0],         // AdapterFormat (display mode format)
        (D3DFORMAT)pConfig2[1],         // BackBufferFormat
        (BOOL)(pConfig1[3] & 0xFF)      // bWindowed (low byte of 4th DWORD)
    );
    if (FAILED(hr))
        return 4;

    // Re-check D3D object (defensive coding)
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (g_pD3D == nullptr)
            return 4;
    }

    // CheckDeviceFormat: validate depth/stencil or other format support
    hr = g_pD3D->CheckDeviceFormat(
        pConfig1[0],                     // Adapter
        (D3DDEVTYPE)pConfig1[1],        // DeviceType
        (D3DFORMAT)pConfig2[0],         // AdapterFormat
        1,                              // Usage (likely D3DUSAGE_DEPTHSTENCIL)
        (D3DRESOURCETYPE)3,             // ResourceType (D3DRTYPE_SURFACE or D3DRTYPE_TEXTURE)
        (D3DFORMAT)0x72                 // CheckFormat (e.g., D3DFMT_D24S8)
    );
    if (FAILED(hr))
        return 4;

    // Final check: another format validation with high usage flag
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (g_pD3D == nullptr)
            return 4;
    }

    hr = g_pD3D->CheckDeviceFormat(
        pConfig1[0],                     // Adapter
        (D3DDEVTYPE)pConfig1[1],        // DeviceType
        (D3DFORMAT)pConfig2[0],         // AdapterFormat
        0x80000,                        // Usage (e.g., D3DUSAGE_RENDERTARGET)
        (D3DRESOURCETYPE)3,             // ResourceType (texture)
        (D3DFORMAT)pConfig2[1]          // BackBufferFormat
    );
    if (FAILED(hr))
        return 4;

    return 9; // All validations passed
}