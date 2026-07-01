// FUNC_NAME: RenderDevice::drawSpriteWithAlpha
void __thiscall RenderDevice::drawSpriteWithAlpha(int *param_1, int textureHandle, int alphaMultiplier)
{
    // param_1 is a pointer to a SpriteDrawData structure (handle)
    // textureHandle: texture ID or handle
    // alphaMultiplier: global alpha scale (0-255)

    SpriteDrawData* drawData = (SpriteDrawData*)*param_1; // dereference handle

    // Extract color and alpha from first 8 bytes
    uint colorLow = (uint)(drawData->colorAndAlpha);      // +0x00 low 32 bits (RGB?)
    float alphaHigh = (float)((ulonglong)drawData->colorAndAlpha >> 32); // high 32 bits as float
    float alpha = 1.0f - alphaHigh; // invert? Possibly premultiplied alpha

    // Second 8 bytes (UV or additional color)
    uint64_t uvOrColor2 = drawData->uvOrColor2; // +0x08

    // Alpha scaling for two color components
    uint color1 = drawData->color1; // +0x10? Actually puVar1+4 is offset 0x20? Need to map correctly.
    // From decompile: *(uint *)(puVar1 + 4) -> offset 0x20 (since puVar1 is 8-byte elements)
    // and *(uint *)((int)puVar1 + 0x24) -> offset 0x24
    uint color1Alpha = (color1 >> 24) & 0xFF;
    uint color2Alpha = (drawData->color2 >> 24) & 0xFF; // +0x24

    // Scale alpha by alphaMultiplier
    uint scaledAlpha1 = (color1Alpha * alphaMultiplier) / 0xFF;
    uint scaledAlpha2 = (color2Alpha * alphaMultiplier) / 0xFF;

    // Rebuild colors with scaled alpha
    uint finalColor1 = (color1 & 0x00FFFFFF) | (scaledAlpha1 << 24);
    uint finalColor2 = (color2 & 0x00FFFFFF) | (scaledAlpha2 << 24);

    // Additional fields
    uint extra1 = drawData->extra1; // +0x28 (local_18)
    uint extra2 = drawData->extra2; // +0x2c (local_14)

    // Set texture and shader states
    RenderDevice::setTexture(drawData->textureHandle); // +0x10 (puVar1+2)
    RenderDevice::setColor(&finalColor1, 0); // second param 0
    RenderDevice::setSomething(drawData->someField); // +0x14 (from *param_1+0x14)

    // Write to global render state
    g_renderDevice[0x34] = drawData->someOtherField; // +0x1c

    // Draw call
    RenderDevice::drawQuad(
        colorLow,                // color
        alpha,                   // alpha
        (uint)uvOrColor2,        // uv/u1
        (uint)(uvOrColor2 >> 32),// uv/v1
        drawData->field18,       // +0x18
        textureHandle,           // param_2
        drawData->field30,       // +0x30
        drawData->field34,       // +0x34
        &extra1,                 // pointer to extra1
        0,                       // unknown
        &finalColor2,            // pointer to finalColor2
        0, 0, 0,                 // zeros
        0xFFFFFFFF,              // -1
        1                        // bool
    );
}