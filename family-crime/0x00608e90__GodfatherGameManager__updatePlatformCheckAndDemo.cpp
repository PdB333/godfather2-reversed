// FUNC_NAME: GodfatherGameManager::updatePlatformCheckAndDemo
// Address: 0x00608e90
// Called from main loop at 0x0060d8b0. Handles platform region detection and demo/replay index updates.

void GodfatherGameManager::updatePlatformCheckAndDemo(void)
{
    int platformResult;
    DemoPlaybackData* demoDataPtr;

    // Call base update (likely another manager or subsystem)
    FUN_00608dc0();

    // If the platform flag is set, query engine for platform type
    if (g_platformCheckFlag != 0) {
        // Virtual call at offset 0x44 on the global engine object (likely getPlatformID)
        platformResult = (*(code **)(*(int*)g_engineObject + 0x44))(g_engineObject, 0, 0, 0, 0);
        // Magic constant 0x88760868 corresponds to a specific platform (e.g., NTSC or PAL)
        if (platformResult == 0x88760868) {
            g_regionIsPAL = 1;  // Set region flag (offset 0x0119da5e)
        }
    }

    // Compute pointer into the demo data array (each entry 0x38 bytes)
    if (g_demoIndex < 0x1000) {
        demoDataPtr = &g_demoDataArray[g_demoIndex];  // base at 0x011a0f28, index * 0x38
    } else {
        demoDataPtr = NULL;
    }

    // Handle demo playback based on index
    if (g_demoIndex == -1) {
        FUN_00606830(-1, demoDataPtr);  // Special case: no demo selected
        return;
    }
    FUN_00606830(g_demoIndex, demoDataPtr);
}