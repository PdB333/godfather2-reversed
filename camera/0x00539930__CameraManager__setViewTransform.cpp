// FUNC_NAME: CameraManager::setViewTransform
void __thiscall CameraManager::setViewTransform(float* thisTransform, float* otherTransform)
{
    // Copy first 4 floats from thisTransform into global view transform 1
    gViewTransform1[0] = thisTransform[0];
    gViewTransform1[1] = thisTransform[1];
    gViewTransform1[2] = thisTransform[2];
    gViewTransform1[3] = thisTransform[3];

    // Copy first 4 floats from otherTransform into global view transform 2
    gViewTransform2[0] = otherTransform[0];
    gViewTransform2[1] = otherTransform[1];
    gViewTransform2[2] = otherTransform[2];
    gViewTransform2[3] = otherTransform[3];

    // Check if the current camera is active and the scene is ready
    if (gCurrentCameraPtr == &gDefaultCamera && gCameraState == gSceneState) {
        // Update render data with the new transforms
        updateRenderData(gSceneState, gRenderData1, &gViewTransform1);
        updateRenderData(gSceneState, gRenderData2, &gViewTransform2);
    }
}