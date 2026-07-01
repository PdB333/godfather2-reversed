//FUNC_NAME: HUDManager::updateHUD
// Address: 0x0085c9f0
// Role: Updates HUD vertex data and renders UI elements (likely a gauge/progress bar)

void HUDManager::updateHUD()
{
    int* pState = reinterpret_cast<int*>(this + 8); // +0x08: m_currentState
    int currentState = *pState;

    // If state is valid and not a specific state (0x48 = 72), perform rendering
    if (currentState != 0 && currentState != 0x48)
    {
        int index = (currentState == 0) ? 0 : (currentState - 0x48);
        // Call virtual function at vtable+8 from object at offset 0x1f30 from some base
        int (*func)() = **(int (***)())(*(int*)(index + 0x1f30) + 8);
        int result = func();
        // Apply some effect or color
        FUN_00464a10(result);

        // Update global time or delta if different
        if (g_someFloat != g_anotherFloat) // DAT_0112df58 vs _DAT_00d577a0
        {
            int manager = FUN_007ff880(); // get some manager
            if (manager != 0)
            {
                // Set float at offset 0x188 from nested pointer
                *(float*)(*(int*)(*(int*)(manager + 0x360) + 0x1c) + 0x188) = g_someFloat;
            }
        }

        // Clear flags
        g_flag1 = 0; // DAT_0112df5c
        g_flag2 = 0; // DAT_0112df5d
        g_flag3 = 0; // DAT_0112df60

        // Release current state if non-zero
        if (*pState != 0)
        {
            FUN_004daf90(pState); // likely operator delete
            *pState = 0;
        }

        // Set render states
        FUN_00544ae0(2); // e.g., setBlendMode
        FUN_00544b90(1); // e.g., setAlphaTest

        // Clear screen or begin frame
        int clearColor[3] = {0, 0, 0};
        FUN_005466c0(clearColor);
    }

    // Set viewport, projection, etc.
    FUN_00549a50(0); // setViewport
    FUN_00549a70(0); // setProjection
    FUN_00549ab0(1); // setAlphaTest(true)
    FUN_00549ac0(0); // setBlendMode(0) (masked)
    FUN_00549a90(0); // setDepthTest(false)

    // Update vertex data for UI elements
    int* renderer = *(int**)(this + 4); // +0x04: m_renderer
    int* meshData = *(int**)(renderer + 0x368); // +0x368: m_uiMesh
    unsigned int numVertices = *(unsigned char*)(meshData + 0x20); // +0x20: m_numVertices
    int startOffset = numVertices - *(char*)(*(char**)(meshData + 0x98)); // +0x98: m_startIndex pointer
    unsigned int processed = 0;

    // Process in chunks of 4 vertices (stride 0xa0 = 4 * 0x28)
    if (startOffset > 3)
    {
        int chunkCount = (startOffset - 4) / 4 + 1;
        processed = chunkCount * 4;
        int offset = 0;
        do
        {
            float* vertexData = *(float**)(*(int*)(meshData + 0x8c)); // +0x8c: m_vertexData
            // Write first set of values (e.g., UV or color) to 4 vertices
            vertexData[0x10/4 + offset/4] = g_constant1; // DAT_0112df40
            vertexData[0x0c/4 + offset/4] = g_constant2; // DAT_0112df50
            vertexData[0x38/4 + offset/4] = g_constant1;
            vertexData[0x34/4 + offset/4] = g_constant2;
            vertexData[0x60/4 + offset/4] = g_constant1;
            vertexData[0x5c/4 + offset/4] = g_constant2;
            vertexData[0x88/4 + offset/4] = g_constant1;
            vertexData[0x84/4 + offset/4] = g_constant2;
            offset += 0xa0; // 160 bytes
            chunkCount--;
        } while (chunkCount != 0);
    }

    // Process remaining vertices (less than 4) with stride 0x28
    if (processed < startOffset)
    {
        int offset = processed * 0x28;
        int remaining = startOffset - processed;
        do
        {
            float* vertexData = *(float**)(*(int*)(meshData + 0x8c));
            vertexData[0x10/4 + offset/4] = g_constant1;
            vertexData[0x0c/4 + offset/4] = g_constant2;
            offset += 0x28;
            remaining--;
        } while (remaining != 0);
    }

    // Second set of values (different constants) for the rest of vertices
    if (numVertices - startOffset > 3)
    {
        int offset = startOffset * 0x28;
        int chunkCount = ((numVertices - startOffset) - 4) / 4 + 1;
        startOffset += chunkCount * 4;
        do
        {
            float* vertexData = *(float**)(*(int*)(meshData + 0x8c));
            vertexData[0x10/4 + offset/4] = g_constant3; // DAT_0112df44
            vertexData[0x0c/4 + offset/4] = g_constant4; // DAT_0112df54
            vertexData[0x38/4 + offset/4] = g_constant3;
            vertexData[0x34/4 + offset/4] = g_constant4;
            vertexData[0x60/4 + offset/4] = g_constant3;
            vertexData[0x5c/4 + offset/4] = g_constant4;
            vertexData[0x88/4 + offset/4] = g_constant3;
            vertexData[0x84/4 + offset/4] = g_constant4;
            offset += 0xa0;
            chunkCount--;
        } while (chunkCount != 0);
    }

    // Remaining vertices for second set
    if (startOffset < numVertices)
    {
        int offset = startOffset * 0x28;
        int remaining = numVertices - startOffset;
        do
        {
            float* vertexData = *(float**)(*(int*)(meshData + 0x8c));
            vertexData[0x10/4 + offset/4] = g_constant3;
            vertexData[0x0c/4 + offset/4] = g_constant4;
            offset += 0x28;
            remaining--;
        } while (remaining != 0);
    }

    // Set final constant to another buffer
    *(float*)(*(int*)(*(int*)(this + 4) + 0x38c) + 0xc) = g_constant5; // DAT_0112df48
}