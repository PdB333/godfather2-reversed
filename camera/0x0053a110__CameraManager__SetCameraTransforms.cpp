// FUNC_NAME: CameraManager::SetCameraTransforms

void __thiscall CameraManager::SetCameraTransforms(uint32_t* pWorldData, uint32_t* pViewData)
{
    // Copy world transform data (4 DWORDs, likely a 4x4 matrix row or a float4) from input to global buffer
    // Offset 0x0121b8a0: gCameraWorldBuffer[4]
    gCameraWorldBuffer[0] = pWorldData[0];
    gCameraWorldBuffer[1] = pWorldData[1];
    gCameraWorldBuffer[2] = pWorldData[2];
    gCameraWorldBuffer[3] = pWorldData[3];

    // Copy view transform data (4 DWORDs) to global buffer
    // Offset 0x0121b8b0: gCameraViewBuffer[4]
    gCameraViewBuffer[0] = pViewData[0];
    gCameraViewBuffer[1] = pViewData[1];
    gCameraViewBuffer[2] = pViewData[2];
    gCameraViewBuffer[3] = pViewData[3];

    // Check if the current render pass is the main scene pass and the scene manager state is active
    // DAT_012058e8 - gCurrentRenderPass (pointer to current pass object)
    // DAT_0121b740 - gSceneRenderPass (static scene pass instance)
    // DAT_0121b754 - gSceneState (pointer/state)
    // DAT_0121bbbc - gSceneManager (pointer to scene manager)
    if ((gCurrentRenderPass == &gSceneRenderPass) && (gSceneState == gSceneManager))
    {
        // Register/update the world and view matrices in the scene manager
        // DAT_0121bb68 - gSceneRenderData (array or object list for rendering)
        FUN_0060add0(gSceneManager, gSceneRenderData, &gCameraWorldBuffer);
        FUN_0060add0(gSceneManager, gSceneRenderData, &gCameraViewBuffer);
    }
}