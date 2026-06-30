// FUNC_NAME: CameraManager::setActiveCamera
// Function address: 0x005d8a70
// Sets the requested camera as the active camera, releases old references,
// and updates view/projection transforms if the camera has valid data.

extern int* g_activeCamera; // global pointer to the currently active camera

// Forward declarations of engine helper functions
void __fastcall releaseObject(int obj);
void __fastcall updateCameraTransform(int target, int source, float* outTransform);
void __fastcall updateCameraProjection(int target, int fov, int nearPlane);

void __fastcall CameraManager::setActiveCamera(int camera)
{
    // Check if this camera is already active
    if (g_activeCamera == camera)
    {
        // Already active – just clear the active flag
        *(int*)(camera + 0xa4) = 0; // +0xa4: active flag (0 = not active)
    }
    else
    {
        // Mark as active and update global pointer
        *(int*)(camera + 0xa4) = 1; // +0xa4: active flag (1 = active)
        g_activeCamera = camera;

        // Release previous view objects (e.g. old view, old projection)
        releaseObject(*(int*)(camera + 0x10)); // +0x10: previous view pointer
        releaseObject(*(int*)(camera + 0x14)); // +0x14: previous projection pointer
    }

    // If the camera has a valid transform (boolean at +0xc0), update matrices
    if (*(char*)(camera + 0xc0) != '\0') // +0xc0: hasValidTransform flag
    {
        // Update lookAt transform: render target (0x104), position (0xf8), lookAt (0xe0)
        updateCameraTransform(*(int*)(camera + 0x104),
                              *(int*)(camera + 0xf8),
                              (float*)(camera + 0xe0));

        // Update up/right transform: render target (0x104), upVector (0xf4), right (0xd0)
        updateCameraTransform(*(int*)(camera + 0x104),
                              *(int*)(camera + 0xf4),
                              (float*)(camera + 0xd0));

        // Update projection: render target (0x104), fov (0xfc), nearPlane (0xf0)
        updateCameraProjection(*(int*)(camera + 0x104),
                               *(int*)(camera + 0xfc),
                               *(int*)(camera + 0xf0));
    }
}