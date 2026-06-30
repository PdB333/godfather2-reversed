// FUNC_NAME: RenderDevice::configureBackBuffer
void __thiscall RenderDevice::configureBackBuffer(uint param_2) {
    // Initialize device with a known hash (potentially a class ID or format token)
    initializeDevice(param_2, 0x246a9b4e);
    resetDevice(0);

    // Check if vertical sync is enabled or double buffering is active
    if (!isVerticalSyncEnabled()) {
        // Retrieve device capabilities structure
        DeviceCaps* caps = getDeviceCaps();
        uint capsFlags = caps->flags;  // +0x08: flags field

        // Set back buffer presentation mode (clear low byte except bit 0 after shift)
        setPresentationMode(capsFlags >> 1 & 0xffffff01);
        // Set front buffer presentation mode (clear low byte except bit 0)
        setFrontBufferMode(capsFlags & 0xffffff01);
    }
}