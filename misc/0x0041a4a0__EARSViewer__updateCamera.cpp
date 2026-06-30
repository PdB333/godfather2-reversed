// FUNC_NAME: EARSViewer::updateCamera
// Function at 0x0041a4a0: Updates camera view matrix, FOV, and other rendering parameters for the EARS viewer.
// Called from EARSViewerManager at 0x004310d0. The 'this' pointer (param_1) is a Viewer object; param_2 is a Player object.
void __thiscall EARSViewer::updateCamera(void *this, void *playerObj, uint param3, uint param4)
{
    // Get pointer to camera state from this+4 (likely a struct with matrices and other data)
    CameraState *pCamera = *(CameraState **)((char *)this + 4);
    float viewMatrix[16]; // 4x4 matrix stored at local_50 (16 floats)

    // Engine-specific setup: clear possibly previous matrix and perform some initialisation
    FUN_00493120(); // Unknown: likely clear some render state
    FUN_00417560(); // Unknown: prepare matrix stack or similar

    // Copy the newly computed matrix from stack into pCamera at offset 0x200 (64 bytes = 16 floats)
    // This is the view matrix (world->camera transform)
    pCamera->viewMatrix[0]  = viewMatrix[0];
    pCamera->viewMatrix[1]  = viewMatrix[1];
    pCamera->viewMatrix[2]  = viewMatrix[2];
    pCamera->viewMatrix[3]  = viewMatrix[3];
    pCamera->viewMatrix[4]  = viewMatrix[4];
    pCamera->viewMatrix[5]  = viewMatrix[5];
    pCamera->viewMatrix[6]  = viewMatrix[6];
    pCamera->viewMatrix[7]  = viewMatrix[7];
    pCamera->viewMatrix[8]  = viewMatrix[8];
    pCamera->viewMatrix[9]  = viewMatrix[9];
    pCamera->viewMatrix[10] = viewMatrix[10];
    pCamera->viewMatrix[11] = viewMatrix[11];
    pCamera->viewMatrix[12] = viewMatrix[12];
    pCamera->viewMatrix[13] = viewMatrix[13];
    pCamera->viewMatrix[14] = viewMatrix[14];
    pCamera->viewMatrix[15] = viewMatrix[15];

    // If this is the main viewer instance, push the matrix to the rendering engine
    if (g_pMainViewer == pCamera)
    {
        // FUN_0060b020: Push view matrix to engine (arguments: entity handle at pCamera+0x14, some offset at pCamera+0x1f8, and the matrix)
        FUN_0060b020(*(undefined4 *)(pCamera + 0x14), *(undefined4 *)(pCamera + 0x1f8), pCamera->viewMatrix);
    }

    // Get some per-thread or global index (FS segment offset 0x2c -> pointer to something)
    // In Windows FS:[0x2c] is the pointer to the current thread's scope table; here it's used to get a table base.
    int *pThreadData = **(int ***)(__readfsdword(0x2c) + 0x28); // adjusted based on typical layout
    // Actually the decompiled code shows: iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c);
    // We'll just leave as a comment: pointer obtained from thread local storage.

    // Compute FOV or clipping values: read a byte from player->someTable + some index
    // playerObj+0x18 is a pointer to another structure (likely player weapon or stance data)
    // at offset 0x9b within that structure there is a byte, multiplied by a scale factor
    // pThreadData+8 gives an index for that table (maybe weapon type or animation state)
    float fFovScale = (float)(*(byte *)(*(int *)((char *)playerObj + 0x18) + 0x9b + *(int *)((char *)pThreadData + 8)));
    float fovFactor = fFovScale * g_fFovScaleGlobal; // DAT_00e44640

    // Write two derived floats to pCamera at offsets 0x264 and 0x268
    // Likely horizontal and vertical FOV or near/far plane distances
    pCamera->field_264 = g_fFovBase - fovFactor; // DAT_00e2b1a4
    pCamera->field_268 = fovFactor;

    // If main viewer, push these values to engine (maybe set projection parameters)
    if (g_pMainViewer == pCamera)
    {
        // FUN_0060ac80: Set camera projection parameters (arguments: entity handle, some offset at pCamera+0x260, and the two floats)
        FUN_0060ac80(*(undefined4 *)(pCamera + 0x14), *(undefined4 *)(pCamera + 0x260), &pCamera->field_264);
    }

    // Finalise update: apply any remaining transforms (calls into another part of the pipeline)
    FUN_00419ce0(playerObj, param3, param4);
}