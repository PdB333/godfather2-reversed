// FUNC_NAME: DebugRenderer::drawLine
void __thiscall DebugRenderer::drawLine(/* this */ DebugRenderer *this, int renderContext, float (*worldMatrix)[4], float *worldPos, float *unknown, float *screenPt1, float *screenPt2, uint32_t color)
{
    float vecWorld[4], vecUnknown[4], vecTemp[4];
    float out1[4], out2[4], out3[4];
    uint32_t swappedColor;
    int *cmdBuffer;
    uint32_t *writePtr;

    // Initialize temporary vector/matrix (likely for internal transformation)
    tempInit(this, vecTemp); // calls FUN_005c5320(param_1), param_1 is this? or vecTemp? We'll treat it as initializing something.

    fVar5 = worldPos[0];
    fVar6 = worldPos[1];
    fVar7 = worldPos[2];
    fVar8 = worldPos[3];

    // Copy unknown vector
    vecUnknown[0] = unknown[0];
    vecUnknown[1] = unknown[1];
    vecUnknown[2] = unknown[2];
    vecUnknown[3] = unknown[3];

    // Copy worldPos to temporary for transformation
    vecWorld[0] = worldPos[0];
    vecWorld[1] = fVar6;
    vecWorld[2] = fVar7;
    vecWorld[3] = fVar8;

    // Transform three vectors (worldPos, unknown, and a copy of unknown?) by worldMatrix
    multiplyMatrixVector(worldMatrix, vecUnknown, out1);   // FUN_0056b420(param_3, &local_60, local_20)
    multiplyMatrixVector(worldMatrix, vecWorld, out2);     // FUN_0056b420(param_3, &local_b0, local_30)
    multiplyMatrixVector(worldMatrix, vecTemp, out3);      // FUN_0056b420(param_3, &local_c0, local_40) - note vecTemp uninitialized? Might be a copy of worldPos.

    // Store screen points (maybe in clip space or screen space)
    float screenX1 = screenPt1[0];
    float screenY1 = screenPt1[1];
    // Compute transformed worldPos (worldMatrix * worldPos) - this overwrites local_50..fStack_44
    float tX = worldMatrix[0][0] * fVar5 + worldMatrix[0][4] * fVar6 + worldMatrix[0][8] * fVar7 + worldMatrix[0][12] * fVar8;
    float tY = worldMatrix[1][0] * fVar5 + worldMatrix[1][4] * fVar6 + worldMatrix[1][8] * fVar7 + worldMatrix[1][12] * fVar8;
    float tZ = worldMatrix[2][0] * fVar5 + worldMatrix[2][4] * fVar6 + worldMatrix[2][8] * fVar7 + worldMatrix[2][12] * fVar8;
    float tW = worldMatrix[3][0] * fVar5 + worldMatrix[3][4] * fVar6 + worldMatrix[3][8] * fVar7 + worldMatrix[3][12] * fVar8;

    float screenX2 = screenPt2[0];
    float screenY2 = screenPt2[1];

    // Copy screen points to adjacent locals (possibly for alignment)
    float scX1 = screenX1;
    float scY1 = screenY1;
    float scX2 = screenX2;
    float scY2 = screenY2;

    // Convert color from ARGB to ABGR (D3D color format swap?)
    swappedColor = ((color & 0x00FF0000) | (color >> 16)) >> 8 | ((color & 0x0000FF00) | (color << 16)) << 8;

    if (debugDrawEnabled) // DAT_0119d0ac == 1
    {
        // Begin command buffer
        beginDebugCommandBuffer(); // FUN_005d8020()
        cmdBuffer = debugCommandBufferPtr; // DAT_01206880

        // Write command header: type pointer and primitive type
        *(void**)(*(int*)(cmdBuffer + 0x14)) = &COMMAND_TYPE_VTABLE_8; // PTR_LAB_01126bb8
        *(int*)(cmdBuffer + 0x14) += 4;
        *(int*)(*(int*)(cmdBuffer + 0x14)) = 8;                         // primitive type (e.g., lines)
        *(int*)(cmdBuffer + 0x14) += 4;

        // Write vertex data header
        *(void**)(*(int*)(cmdBuffer + 0x14)) = &VERTEX_DATA_VTABLE_1;   // PTR_LAB_01126b18
        *(int*)(cmdBuffer + 0x14) += 4;
        // Align and write first vertex component values
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 3) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 1;                                                   // vertex semantic index or size
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 7) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 1;                                                   // another value
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 7) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 5;                                                   // component count
        *(int*)(cmdBuffer + 0x14) += 4;

        // Submit draw command with color
        submitDebugDraw(*(void**)(renderContext + 0x10), swappedColor); // FUN_005d8140(*(param_2+0x10), swappedColor)

        // Second draw primitive (possibly another line or another part)
        beginDebugCommandBuffer();
        cmdBuffer = debugCommandBufferPtr;
        *(void**)(*(int*)(cmdBuffer + 0x14)) = &COMMAND_TYPE_VTABLE_8;
        *(int*)(cmdBuffer + 0x14) += 4;
        *(int*)(*(int*)(cmdBuffer + 0x14)) = 7;                         // different primitive type (e.g., point)
        *(int*)(cmdBuffer + 0x14) += 4;

        *(void**)(*(int*)(cmdBuffer + 0x14)) = &VERTEX_DATA_VTABLE_1;
        *(int*)(cmdBuffer + 0x14) += 4;
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 3) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 1;
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 7) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 7;                                                   // different value
        writePtr = (uint32_t*)((*(int*)(cmdBuffer + 0x14) + 7) & ~3);
        *(int*)(cmdBuffer + 0x14) = (int)writePtr;
        *writePtr = 8;                                                   // another component count / index
        *(int*)(cmdBuffer + 0x14) += 4;

        submitDebugDraw(*(void**)(renderContext + 0x10), swappedColor);
        return;
    }

    // No debug overlay: just submit one draw
    submitDebugDraw(*(void**)(renderContext + 0x10), swappedColor);
}