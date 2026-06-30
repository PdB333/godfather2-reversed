// FUNC_NAME: GameManager::updateFrame
// Address: 0x00614ab0
// Role: Main frame update - copies camera matrix to view matrix, updates input, physics, AI, audio, and renders

void GameManager::updateFrame(void)
{
    // Copy initial transform data (likely from camera to view matrix)
    copyMatrix(&g_someMatrix1, &g_someMatrix2); // FUN_006131d0

    // Process input twice (maybe for two controllers or buffered input)
    processInput(); // FUN_00417560
    processInput(); // FUN_00417560

    // Update physics and AI
    updatePhysics(); // FUN_00611fe0
    updateAI();      // FUN_00612130

    // Copy camera matrix (16 floats) to view matrix
    // Source: g_cameraMatrix (at 0x011f6af0)
    // Destination: g_viewMatrix (at 0x011f6830)
    g_viewMatrix = g_cameraMatrix; // 64-byte copy (4x4 matrix)

    // If render manager exists and has a valid render target, set the view matrix
    if ((g_renderManager != 0) && (g_renderManager->renderTarget != 0)) {
        setViewMatrix(g_renderManager->camera, g_renderManager->renderTarget, &g_viewMatrix); // FUN_0060b020
    }

    // Update audio streams
    updateAudio(&g_audioData); // FUN_00612210

    // Render the frame
    renderFrame(); // FUN_00611ea0
}