// FUNC_NAME: AnimationBlender::getBlendResult(float, AnimationCallback, AnimationCallback)

int AnimationBlender::getBlendResult(float blendValue, AnimationCallback callback1, AnimationCallback callback2) {
    // Clear flag 0x04000000 in flags at +0x10
    *(uint32_t*)(this + 0x10) &= 0xFBFFFFFF;
    int resultHandle = 0;
    uint32_t flags = *(uint32_t*)(this + 0x10);

    // Special sentinel value (e.g., -1.0f or FLT_MAX) indicating "no blend"
    if (blendValue == DAT_00e2b05c) {
        // Check if resource at offset 0x60 is allocated
        if (*(int32_t*)(this + 0x60) != 0) {
            *(uint32_t*)(this + 0x10) = flags | 0x800000;   // Set lock flag
            resultHandle = FUN_00571690();                   // Allocate blend buffer
            *(uint32_t*)(this + 0x10) = flags & 0x20 |      // Preserve some bit
                                         *(uint32_t*)(this + 0x10) & 0xFF7FFFFF;
            if (resultHandle != 0) {
                uint32_t defaultVal = DAT_00e2b1a4;          // Default vector value
                // Zero out quad A (offset 0x90-0x9C) and set quad B (0x80-0x8C) from default
                *(uint32_t*)(this + 0x98) = 0;
                *(uint32_t*)(this + 0x94) = 0;
                *(uint32_t*)(this + 0x90) = 0;
                *(uint32_t*)(this + 0x9C) = defaultVal;
                *(uint32_t*)(this + 0x88) = 0;
                *(uint32_t*)(this + 0x84) = 0;
                *(uint32_t*)(this + 0x80) = 0;
                *(uint32_t*)(this + 0x8C) = defaultVal;
                FUN_00571550(resultHandle);                  // Release temporary buffer
            }
        }
        *(uint32_t*)(this + 0x10) &= 0xFFFFFFF7;             // Clear flag 0x8
        return resultHandle;
    }

    // Normal blending path: set up interpolation and allocate result
    FUN_005715d0(blendValue);                                 // Configure interpolation engine
    resultHandle = FUN_00571690();                             // Get blended result buffer

    // Callbacks: if either is provided, invoke with resultHandle
    if (callback2 != nullptr || callback1 != nullptr) {
        if (resultHandle == 0) goto LAB_005719b9;             // Error: no result
        if (callback2 == nullptr) {
            callback1(resultHandle);                          // Direct callback
        } else {
            callback2(&callback1);                            // Indirect callback (modifies callback1?)
        }
    }

    if (resultHandle != 0) {
        // Copy 16 bytes from result->0x10 to this+0x80 (position/vector A)
        // and 16 bytes from result->0x20 to this+0x90 (position/vector B)
        uint32_t vecA[4];
        uint32_t vecB[4];
        memcpy(vecA, (void*)(resultHandle + 0x10), 16);
        memcpy(vecB, (void*)(resultHandle + 0x20), 16);
        *(uint32_t*)(this + 0x80) = vecA[0];
        *(uint32_t*)(this + 0x84) = vecA[1];
        *(uint32_t*)(this + 0x88) = vecA[2];
        *(uint32_t*)(this + 0x8C) = vecA[3];
        *(uint32_t*)(this + 0x90) = vecB[0];
        *(uint32_t*)(this + 0x94) = vecB[1];
        *(uint32_t*)(this + 0x98) = vecB[2];
        *(uint32_t*)(this + 0x9C) = vecB[3];
        FUN_00571550(resultHandle);                             // Release temporary buffer
        return resultHandle;
    }

LAB_005719b9:
    FUN_00577a90();                                             // Error handling (e.g., log warning)
    return resultHandle;                                        // Usually 0 (failure)
}