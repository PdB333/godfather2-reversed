// FUNC_NAME: UIRenderer::setClipRect
void __thiscall UIRenderer::setClipRect(void* thisPtr, int param2, int param3, int param4, int param5, int param6, int param7, int param8)
{
    float srcX, srcY, srcW, srcH; // source rectangle from param4
    float scaledX, scaledY, scaledW, scaledH; // scaled rectangle

    // Begin render state push
    FUN_005c4bf0();

    // Set origin or offset from param7, param8
    FUN_005c5320(param7, param8);

    // Extract source rectangle from param4 (pointer to 4 floats)
    FUN_005c50c0(param4, &srcX, &srcY, &srcW, &srcH);

    // Scale rectangle using this object's dimensions (width at +0x08, height at +0x0C)
    scaledX = *(float*)((int)thisPtr + 0x08) * srcX;
    scaledY = *(float*)((int)thisPtr + 0x0C) * srcY;
    scaledW = (srcW - srcX) * *(float*)((int)thisPtr + 0x08);
    scaledH = (srcH - srcY) * *(float*)((int)thisPtr + 0x0C);

    // Debug visualization if enabled
    if (g_debugFlag != 0 && *(char*)(g_debugFlag + 0xAC) != '\0') {
        FUN_009be4b0(); // debug draw rectangle
    }

    // Push a new command onto the render command list
    int* commandListPtr = (int*)(g_renderCommandList + 0x14);
    **(int**)(g_renderCommandList + 0x14) = &PTR_LAB_00e56768; // set vtable for command
    *commandListPtr = *commandListPtr + 4; // advance command list pointer

    // Copy scaled rectangle data (16 bytes) into command buffer
    FUN_0049c430(&scaledX, 0x10, 0x10);

    // End render state push
    FUN_005c4ac0();
    return;
}