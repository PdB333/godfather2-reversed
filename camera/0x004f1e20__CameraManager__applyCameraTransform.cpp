// FUNC_NAME: CameraManager::applyCameraTransform

void __thiscall CameraManager::applyCameraTransform(CameraManager* this)
{
    // Stack variable for matrix stack handle
    MatrixStackHandle matrixStackHandle;
    // Flag to track if projection matrix has been set
    bool projectionSet = false;
    // Temporary variables for matrix data
    float tempFloat1, tempFloat2, tempFloat3, tempFloat4;
    // Allocated buffer for GPU data
    float* gpuBuffer;

    // Push matrix onto stack; type depends on whether this is a projection matrix
    // this->isProjectionMatrix at +0x60
    int matrixType = (this->isProjectionMatrix != 0) ? 0x100 : 0x40;
    pushMatrix(&matrixStackHandle, matrixType);

    // Set identity matrix
    setIdentityMatrix(0);

    // Clamp global render settings (likely screen dimensions or quality)
    if (g_renderWidth < 0xe) {
        g_renderWidth = 0xe;
    }
    if (0xe < g_renderHeight) {
        g_renderHeight = 0xe;
    }
    g_someFlag1 = 0;
    if (g_renderWidth < 0x1b) {
        g_renderWidth = 0x1b;
    }
    if (0x1a < g_renderHeight) {
        g_renderHeight = 0x1b;
    }
    g_someFlag2 = 1;

    // Begin frame / clear buffers
    beginFrame();

    // Store global matrix handle
    matrixStackHandle = g_globalMatrixHandle;

    // Set render state (e.g., depth test)
    setRenderState(1);

    // Copy camera position/rotation from this object to globals
    // Offsets +0x10, +0x14, +0x18, +0x1c likely represent a 4-component vector (position or quaternion)
    g_cameraPosX = *(float*)((char*)this + 0x10);
    g_cameraPosY = *(float*)((char*)this + 0x14);
    g_cameraPosZ = *(float*)((char*)this + 0x18);
    g_cameraPosW = *(float*)((char*)this + 0x1c);

    // If a specific global pointer matches and a related object exists, apply additional transform
    if ((g_somePointer == &g_someStruct) && (*(int*)((char*)&g_someArray + (uint)g_someIndex * 0x30) != 0))
    {
        applyTransform(g_someData, *(int*)((char*)&g_someArray + (uint)g_someIndex * 0x30), (float*)((char*)this + 0x10));
    }

    // Pop matrix stack
    popMatrix();

    // Set projection matrix if not already set
    if (!projectionSet) {
        setProjectionMatrix(0, 1.0f);
        projectionSet = true;
    }

    // Allocate GPU buffer (5 elements of 4 bytes? Actually writes 32 floats, so likely 128 bytes)
    gpuBuffer = (float*)allocateGPUBuffer(5, 4, 0, 1, 0);
    if (gpuBuffer != nullptr) {
        // Copy transformation data from this object into the buffer
        // This appears to be a 4x4 matrix or a set of vectors
        // Offsets: +0x20, +0x24, +0x28, +0x50 (first row/column)
        gpuBuffer[0] = *(float*)((char*)this + 0x20);
        gpuBuffer[1] = *(float*)((char*)this + 0x24);
        gpuBuffer[2] = *(float*)((char*)this + 0x28);
        gpuBuffer[3] = *(float*)((char*)this + 0x50);

        // Clear next four entries (possibly padding or second matrix)
        gpuBuffer[4] = 0.0f;
        gpuBuffer[5] = 0.0f;
        gpuBuffer[6] = 0.0f;
        gpuBuffer[7] = 0.0f;

        // Second row/column from +0x2c, +0x30, +0x34, +0x50
        gpuBuffer[8] = *(float*)((char*)this + 0x2c);
        gpuBuffer[9] = *(float*)((char*)this + 0x30);
        gpuBuffer[10] = *(float*)((char*)this + 0x34);
        gpuBuffer[11] = *(float*)((char*)this + 0x50);

        // Third row/column from +0x38, +0x3c, +0x40, +0x54
        gpuBuffer[12] = *(float*)((char*)this + 0x38);
        gpuBuffer[13] = *(float*)((char*)this + 0x3c);
        gpuBuffer[14] = *(float*)((char*)this + 0x40);
        gpuBuffer[15] = *(float*)((char*)this + 0x54);

        // Fourth row/column from +0x44, +0x48, +0x4c, +0x54
        gpuBuffer[16] = *(float*)((char*)this + 0x44);
        gpuBuffer[17] = *(float*)((char*)this + 0x48);
        gpuBuffer[18] = *(float*)((char*)this + 0x4c);
        gpuBuffer[19] = *(float*)((char*)this + 0x54);

        // Remaining entries set to global matrix handle or zero
        gpuBuffer[20] = g_globalMatrixHandle;
        gpuBuffer[21] = g_globalMatrixHandle;
        gpuBuffer[22] = 0.0f;
        gpuBuffer[23] = 0.0f;

        // Submit buffer to GPU
        submitGPUBuffer();
    }

    // Pop matrix stack (cleanup)
    popMatrix(&matrixStackHandle);
}