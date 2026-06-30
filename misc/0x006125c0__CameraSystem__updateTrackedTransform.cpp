// FUNC_NAME: CameraSystem::updateTrackedTransform
void __fastcall CameraSystem::updateTrackedTransform(void* /* ecx unused */, float* pTransform)
{
    // pTransform points to 4 floats: likely X, Y, Z, W (quaternion or extended position)
    float f0 = pTransform[0];
    float f1 = pTransform[1];
    float f2 = pTransform[2];
    float f3 = pTransform[3];

    // Static previous transform storage (addresses 0x011f6710, 0x011f6714, 0x011f6718, 0x011f671c)
    static float s_prevTransform[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    // Build mask of unchanged components using SSE comparison semantics:
    // movmskps returns bit 0 set if f0 == s_prev[0], bit 1 if f1 == s_prev[1], etc.
    int mask = 0;
    if (f0 == s_prevTransform[0]) mask |= 1;
    if (f1 == s_prevTransform[1]) mask |= 2;
    if (f2 == s_prevTransform[2]) mask |= 4;
    if (f3 == s_prevTransform[3]) mask |= 8;

    // Update stored previous values
    s_prevTransform[0] = f0;
    s_prevTransform[1] = f1;
    s_prevTransform[2] = f2;
    s_prevTransform[3] = f3;

    // If any component changed (mask != 0xF) and the global camera manager exists
    // DAT_012058e8 is a singleton pointer to CameraManager (or similar)
    void* g_cameraManager = (void*)0x012058e8; // placeholder, actually a global variable
    if ((mask != 0xF) && (g_cameraManager != 0))
    {
        // Offset 0x70 points to a callback function (likely a method)
        // Offset 0x14 is some context pointer passed to the callback
        void* callback = *(void**)((int)g_cameraManager + 0x70);
        void* context = *(void**)((int)g_cameraManager + 0x14);
        if (callback != 0)
        {
            // Call the callback: FUN_0060add0(context, callback, pTransform)
            // This likely notifies the camera system of the changed transform
            void(*notifyFunc)(void*, void*, float*) = (void(*)(void*, void*, float*))0x0060add0;
            notifyFunc(context, callback, pTransform);
        }
    }
}