// FUNC_NAME: Sprite::submitRenderCommand
void __fastcall Sprite::submitRenderCommand(Sprite* thisPtr)
{
    // Get material pointer (offset +0x04)
    Material* material = *(Material**)((char*)thisPtr + 4);
    // Animation time from material (offset +0x8c)
    float animTime = *(float*)((char*)material + 0x8c);
    // Animation frame index (offset +0x0e)
    short frameIndex = *(short*)((char*)thisPtr + 0x0e);
    // Calculate frame data pointer: material->animFrames + frameIndex * 0x24
    int frameDataPtr = *(int*)((char*)material + 0x10) + 0x30 + frameIndex * 0x24;
    // Frame parameters (each frame is 0x24 bytes)
    float frameStart1 = *(float*)(frameDataPtr + 0x18);
    float frameInvDuration1 = *(float*)(frameDataPtr + 0x14);
    float frameStart2 = *(float*)(frameDataPtr + 0x20);
    float frameInvDuration2 = *(float*)(frameDataPtr + 0x1c);
    // Compute interpolated values with clamping
    float val1 = (animTime - frameStart1) * frameInvDuration1;
    if (val1 > 0.0f) {
        if (val1 > g_maxClamp) val1 = g_maxClamp;
    } else {
        val1 = 0.0f;
    }
    float val2 = (animTime - frameStart2) * frameInvDuration2;
    float clampedVal2 = 0.0f;
    if (val2 > 0.0f) {
        clampedVal2 = val2;
        if (val2 > g_maxClamp) clampedVal2 = g_maxClamp;
    }
    // Sprite color components (offset +0x2c, +0x34)
    uint32_t color1 = *(uint32_t*)((char*)thisPtr + 0x2c);
    uint32_t color2 = *(uint32_t*)((char*)thisPtr + 0x34);
    // Sprite scale factors (offset +0x30, +0x38)
    float scaleX = *(float*)((char*)thisPtr + 0x30);
    float scaleY = *(float*)((char*)thisPtr + 0x38);
    // Final multiplier
    float multiplier = clampedVal2 * val1 * scaleY * scaleX;
    // Access render command list write pointer (global at DAT_01206880 + 0x14)
    int* writePtr = *(int**)(g_renderList + 0x14);
    // Write vtable pointer for the command
    *(void**)writePtr = (void*)&g_spriteCommandVTable;
    writePtr++;
    // Write this pointer (sprite instance)
    *writePtr = (int)thisPtr;
    writePtr++;
    // Align to 4-byte boundary (with padding)
    int* alignedPtr = (int*)(((int)writePtr + 7) & 0xfffffffc);
    // Write 64-bit color data (color2 in high 32 bits, color1 in low)
    *(uint64_t*)alignedPtr = ((uint64_t)color2 << 32) | color1;
    // Write multiplier at offset 8 from alignedPtr
    *(float*)(alignedPtr + 2) = multiplier;
    // Update write pointer (advance by 12 bytes from alignedPtr)
    *(int**)(g_renderList + 0x14) = (int*)((char*)alignedPtr + 12);
}