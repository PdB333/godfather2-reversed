// FUNC_NAME: GraphicsDevice::applyDisplaySettings
// Reconstructed from Ghidra at address 0x006b3cc0
// Handles presentation parameters and flipping

void __thiscall GraphicsDevice::applyDisplaySettings(GraphicsDevice *this)
{
    // +0x40: current flip state identifier (magic 0x637b907)
    int flipState = *(int *)(this + 0x40);
    if (flipState != 0x637b907) {
        // +0x3c: previous flip state identifier
        if (*(int *)(this + 0x3c) == 0x637b907) {
            // Log "SPGP FLIP" with the surface/format at +0x38
            logDebugString(0x53504750, 0x464c4950, *(undefined4 *)(this + 0x38));
            // Set presentation interval to 0x20 (32) – maybe D3DPRESENT_INTERVAL_DEFAULT?
            setPresentationInterval(0x20);
            // Configure swap chain: +0xd8 is pointer to swap chain descriptor, param 2 is effect (likely D3DSWAPEFFECT_COPY)
            setSwapChainParameters(*(undefined4 *)(this + 0xd8), 2);
        }
        goto exit;
    }
    // Current flip state matches sentinel; update presentation interval based on display mode
    logDebugString(0x53504750, 0x464c4950, *(undefined4 *)(this + 0x38));
    int interval;
    switch (*(int *)(this + 0xc4)) { // +0xc4: display mode (0=fullscreen,1=windowed,2=?,5=? )
        case 0:
            interval = 0x1a; // 26 – likely immediate vsync
            break;
        case 1:
            interval = 0x1b; // 27 – vsync once per frame
            break;
        case 2:
            interval = 0x1c; // 28 – vsync twice?
            break;
        case 5:
            interval = 0x22; // 34 – unknown
            break;
        default:
            interval = 0; // fallback
    }
    setPresentationInterval(interval);
    setSwapChainParameters(*(undefined4 *)(this + 0xd8), 2);
    // Possibly perform additional device setting update
    updateDisplaySettings();

exit:
    // +0xd4: flag indicating device reset needed
    if (*(int *)(this + 0xd4) != 0) {
        resetGraphicsDevice();
    }
}