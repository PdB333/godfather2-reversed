// FUNC_NAME: RenderDevice::init
// Address: 0x008f2a60
// This function initializes a rendering device with a given window handle.
// It checks for available display adapters (pointers at offsets 0x4c-0x58 of a global config)
// and sets up a device reset callback accordingly.
// The global DAT_0112e241 is set to indicate device initialization is in progress.

// Known globals (renamed):
// DAT_011299bc = g_renderConfig (some structure containing adapter pointers)
// DAT_0112fe18 = g_renderDevice (global render device object)
// DAT_0112e241 = g_deviceInitInProgress (flag)

// Known function calls (renamed based on likely engine patterns):
// FUN_00408680 = someObjectConstruct (constructs or resets the render device object)
// FUN_004c0b90 = createRenderDevice (creates DirectX device with optional reset callback)
// FUN_0040c1f0 = setClearColor (alpha, red, green, blue) - note the mask 0xff000000

void __thiscall RenderDevice::init(void* this, uintptr_t hWnd)
{
    void* deviceResetCallback = nullptr;

    g_deviceInitInProgress = 1;

    // Check if any display adapter is present (at offsets 0x4c, 0x50, 0x54, 0x58)
    // These likely represent primary, secondary, etc. adapters in a config structure.
    if (((*(int*)(g_renderConfig + 0x4c) != 0) ||
         (*(int*)(g_renderConfig + 0x50) != 0)) ||
        ((*(int*)(g_renderConfig + 0x54) != 0) ||
         (*(int*)(g_renderConfig + 0x58) != 0)))
    {
        // Set the reset callback to a known function (LAB_008f20b0)
        deviceResetCallback = &RenderDevice::onDeviceReset;
    }

    // Initialize the global render device object (probably clears or resets it)
    someObjectConstruct(&g_renderDevice);

    // Store the window handle in the render device instance (offset 0x1c)
    *(uintptr_t*)((unsigned char*)this + 0x1c) = hWnd;

    // Create the actual rendering device with the window handle and optional callback
    createRenderDevice(&g_renderDevice, hWnd, deviceResetCallback);

    // Set the clear color to black with full alpha (0xFF000000 = A=255, R=0, G=0, B=0)
    // Parameters: (color, ?, ?, flags?) - typical pattern for DX clear color setup
    setClearColor(0xff000000, 0, 0, 1);
}