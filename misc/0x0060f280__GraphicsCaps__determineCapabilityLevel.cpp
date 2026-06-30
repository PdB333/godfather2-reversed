// FUNC_NAME: GraphicsCaps::determineCapabilityLevel
// Address: 0x0060f280
// This function queries Direct3D9 to determine the highest supported shader/feature level
// for the primary adapter. It uses a global override (g_forceCapLevel) if set.
// The result is stored in g_capLevel (0 = unknown, 1 = basic, 2 = higher).
// The function checks multiple device type/format combinations to infer capability.

#include <d3d9.h>

// Global Direct3D9 interface pointer (initialized elsewhere)
IDirect3D9* g_pD3D = nullptr;

// Override capability level; if not -1, skip detection.
int g_forceCapLevel = -1;

// Resulting capability level (0 = fallback, 1 = low, 2 = high)
int g_capLevel = 0;

void GraphicsCaps::determineCapabilityLevel(int adapterIndex)
{
    if (g_forceCapLevel != -1)
    {
        g_capLevel = g_forceCapLevel;
        return;
    }

    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    IDirect3D9* pD3D = g_pD3D;

    // Heuristic: try to see which device type/format combinations succeed.
    // The exact vtable offset (0x28) corresponds to CheckDeviceType.
    // These calls use varying argument counts to probe different configurations.

    // First probe: adapter + HAL device type (no format info)
    pD3D->CheckDeviceType(adapterIndex, D3DDEVTYPE_HAL);

    // Second probe: adapter + HAL device type only, check result
    HRESULT hr = pD3D->CheckDeviceType(adapterIndex, D3DDEVTYPE_HAL);
    if (FAILED(hr))
    {
        // Even basic HAL fails; set level to 1 (lowest)
        g_capLevel = 1;
        return;
    }

    // Third probe: adapter + HAL + default format + windowed? (full args)
    pD3D->CheckDeviceType(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE);

    // Fourth and fifth probes: same call, but results determine level.
    HRESULT hr4 = pD3D->CheckDeviceType(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE);
    HRESULT hr5 = pD3D->CheckDeviceType(adapterIndex, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE);

    if (SUCCEEDED(hr4))
    {
        g_capLevel = 1;
        return;
    }
    if (SUCCEEDED(hr5))
    {
        g_capLevel = 2;
        return;
    }

    // Fallback level (unaff_EDI likely zero)
    g_capLevel = 0;
}