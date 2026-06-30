// FUNC_NAME: setGlobalShaderConstantBuffer
// Address: 0x00612270
// Copies 16 dwords (64 bytes) from input to a global buffer at 0x011f6930, then optionally forwards to a renderer upload function (FUN_0060b020).

void setGlobalShaderConstantBuffer(const uint32_t *data) {
    // Global buffer for shader constants (4x4 matrix or 16 floats)
    uint32_t *globalBuffer = reinterpret_cast<uint32_t *>(0x011f6930);
    for (int i = 0; i < 16; i++) {
        globalBuffer[i] = data[i];
    }

    // Global renderer context pointer (DAT_012058e8)
    if (DAT_012058e8 != 0) {
        void *rendererContext = *reinterpret_cast<void **>(DAT_012058e8 + 0x10); // +0x10: renderer device/context
        int *constantSlot = *reinterpret_cast<int **>(DAT_012058e8 + 0x54);       // +0x54: pointer to shader constant slot index
        if (constantSlot != 0) {
            // Forward data to engine upload routine
            FUN_0060b020(rendererContext, constantSlot, data);
        }
    }
}