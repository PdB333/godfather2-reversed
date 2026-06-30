// FUNC_NAME: CameraManager::setViewMatrix
#include <cstdint>

// Global view matrix storage (4x4 matrix, 16 floats = 64 bytes)
// Address: 0x011f6690
extern float gViewMatrix[16];

// Singleton pointer to rendering system (e.g., RenderDevice or SceneManager)
extern void* gRenderSystem; // Address: 0x012058e8

// Forward declaration of function that applies matrix to internal camera
void applyMatrixToCamera(void* device, void* camera, float* matrix); // Address: 0x0060b020

/**
 * Stores a 4x4 view matrix into the global buffer and,
 * if the render system is initialized, applies it to the active camera.
 * 
 * @param matrix Pointer to 16 floats (homogeneous 4x4 matrix in row-major order)
 */
void CameraManager::setViewMatrix(float* matrix)
{
    // Copy matrix to global storage (16 floats)
    for (int i = 0; i < 16; i++)
    {
        gViewMatrix[i] = matrix[i];
    }

    // Check if render system is active and has a camera object (offset 0x5c)
    if (gRenderSystem != nullptr)
    {
        void* renderDevice = *(void**)((char*)gRenderSystem + 0x10);  // +0x10: device/context pointer
        void* camera = *(void**)((char*)gRenderSystem + 0x5c);       // +0x5c: active camera object
        if (camera != nullptr)
        {
            applyMatrixToCamera(renderDevice, camera, matrix);
        }
    }
}