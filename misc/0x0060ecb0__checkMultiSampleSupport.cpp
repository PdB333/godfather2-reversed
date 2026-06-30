// FUNC_NAME: checkMultiSampleSupport
#include <d3d9.h>

// Global Direct3D9 object pointer
static LPDIRECT3D9 g_pD3D = nullptr;

// Reconstructed from address 0x0060ecb0
// Checks device format and multisample support for a given configuration.
// Parameters passed via registers ESI and EDI (fastcall-like or custom calling convention):
// ESI: pointer to struct containing adapter index, device type, and some format byte
// EDI: pointer to struct containing adapter format and usage
// Returns 9 on success, 4 on failure.
int checkMultiSampleSupport(const DWORD* pAdapterData, const DWORD* pFormatData)
{
    HRESULT hr;

    // Ensure D3D9 interface is created
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Call IDirect3D9::CheckDeviceFormat
    hr = g_pD3D->CheckDeviceFormat(
        pAdapterData[0],          // Adapter
        (D3DDEVTYPE)pAdapterData[1], // DeviceType
        (D3DFORMAT)pFormatData[0],   // AdapterFormat
        pFormatData[1],            // Usage
        (D3DRESOURCETYPE)*((BYTE*)pAdapterData + 12), // RType (byte at ESI+3?
        (D3DFORMAT)0               // CheckFormat? (missing, maybe default)
    );

    if (FAILED(hr))
        return 4;

    // Ensure D3D9 interface (redundant check preserved)
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Call IDirect3D9::CheckDeviceMultiSampleType (vtable offset 0x28)
    hr = g_pD3D->CheckDeviceMultiSampleType(
        pAdapterData[0],
        (D3DDEVTYPE)pAdapterData[1],
        (D3DFORMAT)pFormatData[0],
        FALSE,
        (D3DMULTISAMPLE_TYPE)3,
        nullptr
    );

    if (FAILED(hr))
        return 4;

    // Ensure D3D9 interface again
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Second call to CheckDeviceMultiSampleType with different multisample type
    hr = g_pD3D->CheckDeviceMultiSampleType(
        pAdapterData[0],
        (D3DDEVTYPE)pAdapterData[1],
        (D3DFORMAT)pFormatData[0],
        FALSE,
        (D3DMULTISAMPLE_TYPE)pFormatData[1],
        nullptr
    );

    // Compute return value: 9 if last call succeeded, 4 if failed
    return (FAILED(hr) ? 4 : 9);
}