// FUNC_NAME: RenderTargetManager::setActiveRenderTarget
void RenderTargetManager::setActiveRenderTarget(uint activeRenderTargetIndex) {
    // Store the active render target index (passed in EAX)
    gActiveRenderTargetIndex = activeRenderTargetIndex;

    // Check global state: gCurrentState == gExpectedState, and gCurrentDevice == gExpectedDevice
    if ((gCurrentState == &gGlobalRenderState) && (gCurrentDevice == gExpectedDevice)) {
        // If a clear flag is set, clear the render target
        if (gClearBufferFlag != 0) {
            clearRenderTarget();
        }

        // If a resize flag is set, recalculate aspect ratio and update viewport
        if (gResizeBufferFlag != 0) {
            // Initialize viewport rectangle to zero
            int viewportX = 0;
            int viewportY = 0;

            // Get the render target descriptor for the active index
            RenderTarget* rtDesc = nullptr;
            if (activeRenderTargetIndex < 0x1000) {
                rtDesc = &gRenderTargetArray[activeRenderTargetIndex];
            }

            // Calculate aspect ratios based on base resolution and texture dimensions
            // gBaseResolution is a float (e.g., 640.0f or 1280.0f)
            float aspectRatioX = gBaseResolution / (float)rtDesc->width;   // offset +2
            float aspectRatioY = gBaseResolution / (float)rtDesc->height;  // offset +4

            // Set the viewport rectangle (x, y, width, height) via the device
            setRenderViewportRectangle(gCurrentDevice, gResizeBufferFlag, &viewportX);
        }
    }
}