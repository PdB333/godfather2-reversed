// FUNC_NAME: RenderDevice::setTexture
void __thiscall RenderDevice::setTexture(int textureId) {
    int *arrayBase; // pointer to array at offset 0x2a8 (relative to this)
    int arrayIndex;
    int somePointer;
    TextureInfo *textureInfo;
    float scaleX, scaleY;

    // +0xe0: current texture ID
    *(int *)(this + 0xe0) = textureId;

    // Check if this is the global render device
    if (g_renderDevice == this) {
        // Read an integer from offset +0x2a8 (maybe an array index)
        arrayIndex = *(int *)(this + 0x2a8);
        // Dereference array at base of this (offset 0) with stride 0x20
        // using arrayIndex to get a pointer offset
        if (*(int *)(this + arrayIndex * 0x20 + 0xec) != 0) {
            // Some helper to handle texture setup (maybe load or bind)
            FUN_006063b0();
        }

        // Get another index: (arrayIndex + 8) * 0x20 relative to this
        somePointer = *(int *)(this + (arrayIndex + 8) * 0x20);
        if (somePointer != 0) {
            // Get texture info from a global table indexed by textureId
            if (textureId < 0x1000) {
                textureInfo = (TextureInfo *)((unsigned char *)g_textureInfoTable + textureId * 0x38);
            } else {
                textureInfo = nullptr;
            }
            if (textureInfo != nullptr) {
                // Calculate scale based on reference resolution
                scaleX = g_referenceResolution / (float)textureInfo->width;
                scaleY = g_referenceResolution / (float)textureInfo->height;
                // Call function to set scaling (maybe projection or viewport)
                // Reads an integer from this+0x14 as argument
                FUN_0060ac80(*(int *)(this + 0x14), somePointer, &scaleX);
            }
        }
    }
}