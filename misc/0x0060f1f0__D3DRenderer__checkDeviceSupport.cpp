// FUNC_NAME: D3DRenderer::checkDeviceSupport
void D3DRenderer::checkDeviceSupport()
{
    // Fetch the adapter format (likely D3DFORMAT) from global state
    uint32_t adapterFormat = s_adapterFormat; // DAT_0120575c

    // Call a helper that might set up device creation parameters or initialize globals
    d3dHelper(s_adapterFormat); // FUN_0060f280

    // Ensure the IDirect3D9 object exists
    if (s_pD3D == nullptr) // DAT_012058cc
    {
        s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    // Attempt to create a D3D device with HAL (hardware) type, passing adapterFormat and behavior flag 1
    // Note: The vtable call at offset 0x28 is assumed to be IDirect3D9::CreateDevice.
    // However, the parameter count (3 total including 'this') suggests a different function signature.
    // The actual parameters may be: (adapter index = adapterFormat, device type = D3DDEVTYPE_HAL, something = 1)
    // We keep the original logic for fidelity.
    HRESULT hr = reinterpret_cast<HRESULT (__stdcall*)(IDirect3D9*, uint32_t, uint32_t)>(
        (*reinterpret_cast<uint32_t**>(s_pD3D))[0x28 / sizeof(void*)])(
            s_pD3D, adapterFormat, 1);

    s_hardwareSupported = (hr >= 0); // DAT_0120587e

    // Set a flag to 0x15 (21) unconditionally after the first attempt
    s_deviceCreationFlag = 0x15; // DAT_00f15a1c

    // Second attempt (redundant check for s_pD3D)
    if (s_pD3D == nullptr)
    {
        s_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    }

    HRESULT hr2 = reinterpret_cast<HRESULT (__stdcall*)(IDirect3D9*, uint32_t, uint32_t)>(
        (*reinterpret_cast<uint32_t**>(s_pD3D))[0x28 / sizeof(void*)])(
            s_pD3D, adapterFormat, 1);

    if (hr2 >= 0)
    {
        // Set flag to 0x4c4c554e ("NULL" in little-endian ASCII)
        s_deviceCreationFlag = 0x4c4c554e;
    }
}