// FUNC_NAME: CameraManager::updateGlobalCameraMatrix
// Address: 0x00612130
// Copies the camera's 4x4 transformation matrix from the CameraManager instance to global storage,
// then updates the GPU constant buffers if a renderer context exists.

void CameraManager::updateGlobalCameraMatrix()
{
    // Copy camera matrix (16 floats = 0x40 bytes) from this object to global view matrix
    // The matrix is the first member of the CameraManager class
    float* src = reinterpret_cast<float*>(this);
    float* dst = reinterpret_cast<float*>(0x011f68a0);
    for (int i = 0; i < 16; i++)
    {
        dst[i] = src[i];
    }

    // Access global renderer context (DAT_012058e8)
    RendererContext* renderer = reinterpret_cast<RendererContext*>(0x012058e8);
    if (renderer != nullptr)
    {
        // Update vertex shader constants for view matrix (offset +0x40)
        if (renderer->viewMatrixHandle != nullptr)
        {
            // FUN_0060b020: Set shader constant (device pointer, handle)
            setShaderConstant(renderer->device, renderer->viewMatrixHandle);
        }
        // Update projection matrix (offset +0x44)
        if (renderer->projectionMatrixHandle != nullptr)
        {
            // FUN_0060aea0: Set shader constant (device pointer, handle)
            setShaderConstant(renderer->device, renderer->projectionMatrixHandle);
        }
    }

    return;
}

// The actual constants at offsets:
// struct RendererContext {
//     +0x00: unknown
//     +0x10: device* (IDirect3DDevice9 or similar)
//     +0x40: handle for view matrix constant (probably a D3DXHANDLE)
//     +0x44: handle for projection matrix constant
// };
// Global g_viewMatrix at 0x011f68a0 (16 floats)