// FUNC_NAME: CameraManager::updateCameraTransform
void CameraManager::updateCameraTransform(void)
{
    // Copy initial matrix data from g_defaultTransform to g_viewTransform (32 bytes = 8 floats, possibly a 2x4 matrix)
    copyMatrixBlock(&g_viewTransform, &g_defaultTransform);

    // Call debug/log checks twice (likely reference counting)
    FUN_00417560();
    FUN_00417560();

    // Reset or update subcomponents
    FUN_00611fe0();
    FUN_00612130();

    // Copy camera view matrix from g_cameraDeviceMatrix to g_viewTransform
    // This overwrites the previous copy with actual device/camera data
    g_viewTransform.m[0] = g_cameraDeviceMatrix.m[0];
    g_viewTransform.m[1] = g_cameraDeviceMatrix.m[1];
    g_viewTransform.m[2] = g_cameraDeviceMatrix.m[2];
    g_viewTransform.m[3] = g_cameraDeviceMatrix.m[3];
    g_viewTransform.m[4] = g_cameraDeviceMatrix.m[4];
    g_viewTransform.m[5] = g_cameraDeviceMatrix.m[5];
    g_viewTransform.m[6] = g_cameraDeviceMatrix.m[6];
    g_viewTransform.m[7] = g_cameraDeviceMatrix.m[7];

    // If a valid camera manager exists and has a camera state object, apply the view transform
    if (g_pCameraManager != 0 && *(int *)(g_pCameraManager + 0x48) != 0)
    {
        // (g_pCameraManager + 0x10) might be a device pointer
        // (g_pCameraManager + 0x48) might be a camera state or transform
        FUN_0060b020(*(undefined4 *)(g_pCameraManager + 0x10), 
                     *(int *)(g_pCameraManager + 0x48), 
                     &g_viewTransform);
    }

    // Finalize update for another camera/input component
    FUN_00612210(&g_cameraInputMatrix);

    // Cleanup or finalize overall update
    FUN_00611ea0();

    return;
}