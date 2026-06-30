// FUNC_NAME: TextureManager::initializeColorScales
void __fastcall TextureManager::initializeColorScales(TextureManager* this)
{
    int i;
    int j;
    float* colorScaleData;
    float* textureData;
    float* colorScalePtr;
    int colorScaleCount;
    uint k;
    float* destPtr;
    float* srcPtr;
    int offset;

    // Initialize first two color scales (indices 0 and 1) with random values
    for (i = 0; i < 3; i++) {
        if (i == 2) {
            // Third color scale (index 2) uses a different random function
            this->colorScaleHandles[2] = FUN_0060a380();
        } else {
            this->colorScaleHandles[i] = FUN_0060a380();
        }

        // Copy 14 floats from constant data to color scale data at offset +0x38*(i+5)
        colorScalePtr = (float*)((int)this + (i + 5) * 0x38);
        textureData = (float*)(&PTR_s_color_scale_010bec4c + (int)colorScalePtr - (int)colorScalePtr);
        // Simplified: offset is difference between static pointer and current address
        // Actually: (int)&PTR_s_color_scale_010bec4c - (int)colorScalePtr
        // But we need real offset: let's just use base pointer
        float* baseColorScaleData = (float*)&PTR_s_color_scale_010bec4c; // +0x010bec4c
        colorScaleCount = 0xe; // 14 floats
        for (j = 0; j < 14; j++) {
            // Copy each float, possibly with some transformation
            colorScalePtr[j] = FUN_0060a580(this->colorScaleHandles[i], baseColorScaleData[j]);
        }
    }

    // Initialize additional color scales (0x58 / 4 = 22, but loop increments by 4 so 22/4 = 5? Actually 0x58 = 88 bytes -> 22 floats, loop: uVar5 += 4 so 22 iterations)
    // Actually uVar5 < 0x58 means 88 iterations? No, uVar5 is incremented by 4, so 88/4 = 22 iterations
    // But destPtr advances by 1 float each time, source advances by 0x3c bytes each time? Let's calculate:
    // destPtr starts at this+0xc0, srcPtr starts at this+0x1c0
    // param_1 (offset from destPtr to PTR) starts at &PTR_PTR_010beac4 - this (which is negative)
    // On each iteration: destPtr++, param_1 -= 0x3c (60 bytes)
    // This seems to iterate over a set of 22 color scale entries, each 15 floats (0x3c bytes)
    // But the inner loop copies 0xf (15) floats from src to dest with some function call

    destPtr = (float*)(this + 0xc0); // +0xc0
    srcPtr = (float*)(this + 0x1c0); // +0x1c0
    offset = (int)&PTR_PTR_010beac4 - (int)this;

    for (k = 0; k < 0x58; k += 4) {
        *destPtr = FUN_0060a2e0(*(undefined4*)(&PTR_PTR_01128330 + k));
        
        // Copy 15 floats from source to destination with transformation
        for (j = 0; j < 0xf; j++) {
            srcPtr[j] = FUN_0060a580(*destPtr, *(float*)((int)srcPtr + offset));
        }
        
        destPtr++;
        offset -= 0x3c; // Move to previous 15-float block
    }
}