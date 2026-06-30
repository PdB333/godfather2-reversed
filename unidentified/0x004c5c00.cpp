// FUN_004c5c00: Light::apply
void __fastcall Light::apply(int thisPtr)
{
    // Render device / context pointer at +0x10
    int *renderDevice = *(int **)(thisPtr + 0x10);
    int *renderDevice2 = *(int **)(thisPtr + 0x14); // secondary device/context

    // Pointer to some data (color set 1) at +0xa4
    int *colorData1 = *(int **)(thisPtr + 0xa4);
    // Pointer to color set 2 at +0xa8
    int *colorData2 = *(int **)(thisPtr + 0xa8);
    // Pointer to color set 3 at +0xb4
    int *colorData3 = *(int **)(thisPtr + 0xb4);

    // Resource pointers to be released
    int *resource1 = *(int **)(thisPtr + 0xac);
    int *resource2 = *(int **)(thisPtr + 0xb0);

    // Additional render data pointers
    int *renderData1 = *(int **)(thisPtr + 0xb8);
    int *renderData2 = *(int **)(thisPtr + 0xf0);

    // Begin lock/update (likely acquire scene)
    beginSceneUpdate();

    // --- First color (non sequential memory: offset order 0xbc, 0xc4, 0xc0)
    float color1[4];
    color1[0] = *(float *)(thisPtr + 0xbc);
    color1[1] = *(float *)(thisPtr + 0xc4);
    color1[2] = *(float *)(thisPtr + 0xc0);
    color1[3] = 0.0f;
    setShaderParameter(renderDevice, colorData1, color1);

    // --- Second color (sequential: 0xd0, 0xd4, 0xd8)
    float color2[4];
    color2[0] = *(float *)(thisPtr + 0xd0);
    color2[1] = *(float *)(thisPtr + 0xd4);
    color2[2] = *(float *)(thisPtr + 0xd8);
    color2[3] = 0.0f;
    setShaderParameter(renderDevice, colorData2, color2);

    // Release any previously allocated resources (if non-null)
    if (resource1 != nullptr) {
        releaseResource();
    }
    if (resource2 != nullptr) {
        releaseResource();
    }

    // --- Third color (single value at +0xc8, stored as float in local[0])
    float color3[4];
    color3[0] = *(float *)(thisPtr + 200); // 0xc8
    color3[1] = 0.0f;
    color3[2] = 0.0f;
    color3[3] = 0.0f;
    setShaderParameter(renderDevice2, colorData3, color3);

    // Apply/commit the light state (probably binding a shader or texture)
    applyLightShader(renderDevice, renderData1, renderData2);
}