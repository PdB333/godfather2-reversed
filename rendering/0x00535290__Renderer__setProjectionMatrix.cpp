// FUNC_NAME: Renderer::setProjectionMatrix
void Renderer::setProjectionMatrix()
{
    // Copy projection matrix from ESI (source) to global render state at 0x01219bd0
    // Matrix is 4x4 (16 floats = 0x40 bytes)
    float (*dest)[4][4] = (float (*)[4][4])0x01219bd0;
    float (*src)[4][4] = (float (*)[4][4])unaff_ESI;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*dest)[i][j] = (*src)[i][j];  // Copy each element
        }
    }
    
    // Check if render context is active and matches the expected render target
    if (DAT_012058e8 == &DAT_01219a70) {
        // Apply the new projection to active render targets
        int renderTargetIndex = (uint)DAT_01219b20;  // Active render target index
        int renderTargetBase = 0x01219cd0;           // Base of render target descriptors
        
        // Set projection on the render target
        int projectionBuffer = *(int *)(renderTargetBase + renderTargetIndex * 0x30);
        if (projectionBuffer != 0) {
            FUN_0060b020(DAT_01219a80, projectionBuffer);  // SetProjectionToBuffer
        }
        
        // Set viewport on the render target
        int viewportBuffer = *(int *)(renderTargetBase + 4 + renderTargetIndex * 0x30);
        if (viewportBuffer != 0) {
            FUN_0060aea0(DAT_01219a80, viewportBuffer);  // SetViewportToBuffer
        }
    }
}