// FUNC_NAME: DisplayManager::initializeDisplay

void DisplayManager::initializeDisplay()
{
    // Global pointer to the display manager singleton
    DisplayManager* pDisplayManager = (DisplayManager*)g_pDisplayManager;

    // Call base graphics initialization
    initializeGraphics();

    // Mark display as initialized (offset +0x154)
    pDisplayManager->m_bInitialized = 1;

    // Set viewport parameters: x=0, y=0, width, height from global constants
    setViewport(0, kViewportX, kViewportY, kViewportWidth, kViewportHeight);

    // Clear the screen (or begin frame) with parameter 0
    clearScreen(0);

    // Get the current display mode handle
    uint displayModeHandle = getCurrentDisplayMode();

    // Retrieve display mode info structure
    DisplayModeInfo* pModeInfo = (DisplayModeInfo*)getDisplayModeInfo(displayModeHandle);

    // Extract width and height from the mode info (offsets +0x02 and +0x04)
    uint16 width = *(uint16*)((uint8*)pModeInfo + 2);
    uint16 height = *(uint16*)((uint8*)pModeInfo + 4);

    // Apply the resolution
    setResolution(width, height);
}