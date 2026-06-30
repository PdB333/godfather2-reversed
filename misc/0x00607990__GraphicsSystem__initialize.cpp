// FUNC_NAME: GraphicsSystem::initialize
void GraphicsSystem::initialize(void)
{
    // Global graphics state initialization
    // DAT_012058b8 and DAT_012058bc are initial width/height settings
    g_renderWidth = g_configWidth;                                          // DAT_0120587c = DAT_012058b8
    g_aspectRatio = (float)g_configWidth / (float)g_configHeight;          // DAT_01205878 = (float)DAT_012058b8 / (float)DAT_012058bc
    g_renderHeight = g_configHeight;                                        // DAT_01205880 = DAT_012058bc
    // Fullscreen flag (0)
    g_fullscreen = 0;                                                       // DAT_01205884 = 0
    // VSync flag (0)
    g_vsync = 0;                                                            // DAT_01205888 = 0
    // Refresh rate denominator (0x411a = 16666 ≈ 1/60 for 60 Hz)
    g_refreshRateDenom = 0x411a;                                            // _DAT_01205890 = 0x411a
    // Refresh rate numerator (0)
    g_refreshRateNum = 0;                                                   // _DAT_01205894 = 0

    // Store some initial byte (probably a flag or mode)
    // _DAT_01205762 = in_AL

    // Check if the graphics subsystem is available (FUN_0060f390 returns 9 for success)
    if (getGraphicsSubsystemVersion() != 9) {
        // Exit if not available
        g_pFatalErrorFunc();                                                // PTR_FUN_00f15a3c
        return;
    }

    // Set up presentation parameters from render width/height
    if (setupPresentationParameters(&g_renderWidth, &g_renderHeight) == '\0') {
        // If setup failed, handle error (FUN_00608b50)
        handleGraphicsError();
    }

    // Store current width/height for comparison later
    g_lastWidth = g_renderWidth;                                            // DAT_0120588c = DAT_0120587c
    g_lastHeight = g_renderHeight;                                          // DAT_01205898 = DAT_01205880

    // Create IDirect3D9 object if not already created
    if (g_pD3D == NULL) {
        g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);                         // D3D_SDK_VERSION = 32 (0x20)
    }

    // Attempt to create device with hardware vertex processing and windowed mode
    // D3DPRESENT_PARAMETERS is stored at g_d3dPresentParams (DAT_01205760)
    // g_hWnd (DAT_0120575c) is the window handle
    // g_d3dBehaviorFlags (DAT_012058b4) is likely D3DCREATE_HARDWARE_VERTEXPROCESSING
    HRESULT hr = g_pD3D->CreateDevice(g_adapterIndex, D3DDEVTYPE_HAL, g_hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &g_presentParams);
    if (FAILED(hr) || g_pDevice == NULL) {
        // On failure, exit with error
        g_pFatalErrorFunc(1);
        return;
    }

    // Get current display mode for backbuffer format
    D3DDISPLAYMODE displayMode;
    g_pD3D->GetAdapterDisplayMode(g_adapterIndex, &displayMode);

    // Check if device supports the requested backbuffer format
    if (g_forceWindowed || (g_displayMode & 2) == 0) {
        g_isWindowed = 1;                                                   // DAT_0120575a = 1
    } else {
        g_isWindowed = 0;                                                   // DAT_0120575a = 0
    }

    // Second device creation attempt? This seems like a fallback with different format
    // or resetting the device with specific parameters (D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING)
    HRESULT hr2 = g_pD3D->CreateDevice(g_adapterIndex, D3DDEVTYPE_HAL, g_hWnd,
                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                       &g_presentParams, displayMode.Format,
                                       D3DFMT_D24S8);                     // 0x100000 = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER? Actually 0x100000 might be D3DPRESENTFLAG_VIDEO or something unknown
    g_deviceCreated = SUCCEEDED(hr2);                                       // DAT_0120575b = (iVar2 >= 0)

    // Set global flags
    g_globalFlag1 = g_capabilityFlag;                                       // DAT_00f15a3b = DAT_00f15a39
    g_globalFlag2 = (g_capabilityFlag != 0) ? 2 : 0;                        // DAT_00f15a48 = -(uint)(DAT_00f15a39 != 0) & 2

    // Initialize some subsystem
    initSubsystem();                                                        // FUN_0060f1f0

    // Set device parameter (vtable offset 0x1d8 is likely SetRenderState or similar)
    g_pDevice->SetRenderState(D3DRS_CULLMODE, g_cullMode);                  // &DAT_01205754 holds the cull mode
}