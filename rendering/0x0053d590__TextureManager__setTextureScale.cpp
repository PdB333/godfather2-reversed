// FUNC_NAME: TextureManager::setTextureScale
void __thiscall TextureManager::setTextureScale(uint32_t textureId) {
    // Store texture ID at +0xe0
    *(uint32_t*)((uint32_t)this + 0xe0) = textureId;

    // Only process for the singleton instance
    if (DAT_012058e8 == (uint32_t)this) {
        // Check if a particular resource is loaded at index from this+0x2a8, array at this+0xec, stride 0x20
        int resourceIndex = *(int*)((uint32_t)this + 0x2a8);
        if (*(int*)((uint32_t)this + 0xec + resourceIndex * 0x20) != 0) {
            // If resource exists, call some load/prepare routine
            FUN_006063b0();
        }

        // Another index calculation: resourceIndex + 8, then use array at base this (offset 0), stride 0x20
        int iVar1 = *(int*)((uint32_t)this + ((resourceIndex + 8) * 0x20));
        if (iVar1 != 0) {
            // Look up texture info from global array based on textureId
            TextureInfo* pTexInfo = NULL;
            if (textureId < 0x1000) {
                pTexInfo = &DAT_011a0f28[textureId]; // stride 0x38
            }

            if (pTexInfo != NULL) {
                // Compute scale factors from texture dimensions
                float scaleX = DAT_00e2cd54 / (float)(*(uint16_t*)((uint32_t)pTexInfo + 2)); // width at +2
                float scaleY = DAT_00e2cd54 / (float)(*(uint16_t*)((uint32_t)pTexInfo + 4)); // height at +4

                // Apply scale to some render object (this+0x14)
                FUN_0060ac80(*(void**)((uint32_t)this + 0x14), iVar1, &scaleX);
            }
        }
    }
}