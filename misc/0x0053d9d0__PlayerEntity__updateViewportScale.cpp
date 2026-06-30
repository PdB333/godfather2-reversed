// FUNC_NAME: PlayerEntity::updateViewportScale
// Function at 0x0053d9d0: Updates viewport scaling for a player entity. ESI holds the player ID (index).
// Globals: g_localPlayerIndex (DAT_0121bf30), g_playerFlags (DAT_01198e84), g_playerCameraState (DAT_01198edc),
//          g_viewportPool (DAT_011a0f28, 0x38-byte entries), g_screenWidth (DAT_00e2cd54),
//          g_cameraManager (DAT_0121be9c)
void PlayerEntity::updateViewportScale() {
    uint playerId = (uint)this; // this is an integer handle/index

    // Check if player has an active flag (e.g., is alive or controllable)
    if (g_playerFlags[g_localPlayerIndex * 0x1b] != 0) {
        clearPendingAction(); // FUN_006063b0 - reset some state
    }

    // Check if player has an active camera state (e.g., not in cutscene)
    if (g_playerCameraState[g_localPlayerIndex * 0x1b] != 0) {
        // Initialize output structure (may be filled by camera update function)
        int32_t out0 = 0;
        int32_t out4 = 0;
        float scaleX = 0.0f;
        float scaleY = 0.0f;

        if (playerId < 0x1000) {
            ViewportData* viewport = &g_viewportPool[playerId]; // each viewport is 0x38 bytes
            // Compute scale factors based on screen width and viewport dimensions
            scaleX = g_screenWidth / (float)viewport->width;    // ushort at +0x2
            scaleY = g_screenWidth / (float)viewport->height;   // ushort at +0x4
        } else {
            viewport = nullptr;
        }

        // Call camera update function with global manager, camera state pointer, and output struct
        updateCameraAspectRatio(g_cameraManager, g_playerCameraState[g_localPlayerIndex * 0x1b], &out0); // FUN_0060add0
    }
}