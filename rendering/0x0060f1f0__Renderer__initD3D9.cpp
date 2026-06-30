// FUNC_NAME: Renderer::initD3D9
// Address: 0x0060f1f0

#include <d3d9.h>

// Global state (defined elsewhere)
extern IDirect3D9* g_pD3D;           // DAT_012058cc
extern uint32_t g_adapterParam;      // DAT_0120575c (adapter index or device type)
extern bool g_bD3DCapable;           // DAT_0120587e
extern uint32_t g_d3dMarker;         // DAT_00f15a1c (0x15 or "NULL")

// Helper called before the D3D9 probe
void preD3DInit(uint32_t param);     // FUN_0060f280

void Renderer::initD3D9()
{
    uint32_t adapter = g_adapterParam;

    // Preliminary setup (e.g., enumerate adapters, validate device type)
    preD3DInit(adapter);

    // Create the Direct3D9 interface if not already present
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Call a Direct3D9 method at vtable offset 0x28
    // Signature: HRESULT (IDirect3D9*, uint32_t, uint32_t)
    // This is likely CheckDeviceType (adapter, deviceType, backBufferFormat, windowed?) 
    // or CheckDeviceFormat with adapter, format, usage, etc.
    // Passes adapter and a hardcoded 1 (e.g., D3DDEVTYPE_HAL or windowed flag)
    typedef HRESULT (__stdcall* D3D9Method)(IDirect3D9*, uint32_t, uint32_t);
    D3D9Method probe = (D3D9Method)(*(uint32_t**)(g_pD3D) + 0x28 / sizeof(uint32_t)); // offset 0x28

    HRESULT hr = probe(g_pD3D, adapter, 1);

    // Set capability flag: true if the call succeeded (hr >= 0)
    g_bD3DCapable = (hr >= 0);

    // Write initial marker (0x15 = 21, perhaps a feature level or version indicator)
    g_d3dMarker = 0x15;

    // Redundant D3D creation check (defensive programming)
    if (g_pD3D == nullptr)
    {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Repeat the same probe
    HRESULT hr2 = probe(g_pD3D, adapter, 1);

    // If the second probe also succeeds, replace marker with ASCII "NULL" (little-endian)
    if (hr2 >= 0)
    {
        g_d3dMarker = 0x4c4c554e; // 'N','U','L','L' in memory
    }
}