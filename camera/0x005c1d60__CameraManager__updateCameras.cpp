// FUNC_NAME: CameraManager::updateCameras
int CameraManager::updateCameras(void)
{
    int *vtable;
    int activePriority;
    int thisPriority;
    int renderResult;
    int *activeCamera;

    // Call virtual function at vtable offset 0x4 (e.g., beginUpdate)
    (**(code **)(*(int *)this + 4))();

    // Check if there is an active camera index (global)
    if ((-1 < activeCameraIndex) &&
        (activeCamera = (int *)cameraArray[activeCameraIndex], activeCamera != (int *)0x0))
    {
        // Get priority from active camera (vtable offset 0x24)
        activePriority = (**(code **)(*activeCamera + 0x24))();
        // Get priority from this camera (vtable offset 0x24)
        thisPriority = (**(code **)(*(int *)this + 0x24))();

        // If active camera has higher or equal priority, let it render
        if (activePriority <= thisPriority) {
            vtable = (int *)*activeCamera;
            // Get render output from this->someMember (+0x10 offset) -> vtable+0x4
            renderResult = (**(code **)(*(int *)(this + 0x10) + 4))();
            // Call active camera's render method (vtable offset 0x1c) with the render output
            (**(code **)(vtable + 0x1c))(renderResult);
        }
    }

    // Call virtual function at vtable offset 0x0 (e.g., endUpdate)
    (**(code **)(*(int *)this))();
    return 1;
}