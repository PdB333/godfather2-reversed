// FUNC_NAME: setGlobalProjectionMatrix

// 0x00612270: Sets the global projection matrix and notifies the render manager if active.
// Globals at 0x011f6930 are a 4x4 matrix (16 floats), likely the view-projection matrix for the game.
// Global at 0x012058e8 is a pointer to a render manager or camera manager (check +0x54, +0x10).

void setGlobalProjectionMatrix(float *matrix)
{
    extern float gProjectionMatrix[16]; // 0x011f6930
    extern void *gpRenderManager;       // 0x012058e8 (some manager with rendering context)

    // Copy the matrix into the global storage
    gProjectionMatrix[0]  = matrix[0];
    gProjectionMatrix[1]  = matrix[1];
    gProjectionMatrix[2]  = matrix[2];
    gProjectionMatrix[3]  = matrix[3];
    gProjectionMatrix[4]  = matrix[4];
    gProjectionMatrix[5]  = matrix[5];
    gProjectionMatrix[6]  = matrix[6];
    gProjectionMatrix[7]  = matrix[7];
    gProjectionMatrix[8]  = matrix[8];
    gProjectionMatrix[9]  = matrix[9];
    gProjectionMatrix[10] = matrix[10];
    gProjectionMatrix[11] = matrix[11];
    gProjectionMatrix[12] = matrix[12];
    gProjectionMatrix[13] = matrix[13];
    gProjectionMatrix[14] = matrix[14];
    gProjectionMatrix[15] = matrix[15];

    // If the render manager exists and has a valid context (offset +0x54 non-zero)
    if (gpRenderManager != 0 && *(int *)((char *)gpRenderManager + 0x54) != 0)
    {
        // Notify the manager – FUN_0060b020 likely applies the projection to the current render target
        // Arguments: some object at +0x10, the context pointer at +0x54, and the matrix
        setProjectionMatrixToContext(
            *(void **)((char *)gpRenderManager + 0x10),   // e.g., render device
            *(void **)((char *)gpRenderManager + 0x54),   // e.g., render context
            matrix
        );
    }
}

// Placeholder for the callee – actual name unknown.
// Typical EA EARS function: RenderManager::setProjectionMatrix or CameraManager::updateMatrix.
void setProjectionMatrixToContext(void *device, void *context, float *matrix); // 0x0060b020