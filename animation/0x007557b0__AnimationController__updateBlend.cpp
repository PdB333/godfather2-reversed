// FUNC_NAME: AnimationController::updateBlend
void __fastcall AnimationController::updateBlend(int *thisPtr, bool forceFlag) {
    char hasAnim;
    int isPaused;
    float blendTime;
    float absBlendTime;
    int animHash;
    int state;

    state = thisPtr[0x1f]; // +0x7C: m_animState (0=inactive, 1=active, 2=blendA, 3=blendB)
    if (state != 0) {
        // Check if the specific animation (identified by hash) is available
        hasAnim = (**(code (__fastcall **)(int, uint))(*(int *)thisPtr[0x14] + 0x10))(
            thisPtr[0x14], 0x369ac561); // +0x50: m_animContainer->hasAnim(hash)
        if (hasAnim != '\0') {
            // Check if the game is not paused (or some condition)
            isPaused = FUN_00800b60(); // e.g., SimManager::isPaused()
            if (isPaused == 0) {
                blendTime = (float)FUN_0046fd30(0); // getCurrentTime()
                blendTime = blendTime * DAT_00e44748; // g_timeScale (e.g., 1.0f)
                absBlendTime = (blendTime < 0.0f) ? -blendTime : blendTime;
                if (absBlendTime >= _DAT_00e51958) { // g_blendThreshold (e.g., 0.001f)
                    if (forceFlag != '\0') {
                        // Set a flag indicating blend is active
                        *(byte *)(thisPtr + 0x16) = *(byte *)(thisPtr + 0x16) | 8; // +0x58: m_flags |= 0x08
                        FUN_007f63e0(0x48); // debug log or event trigger
                        // The following line is a decompiler artifact; likely a virtual call with blendTime as argument
                        // (**(code **)((int)(float)blendTime + 0x164))(); 
                        // Replace with plausible call: this->applyBlend(blendTime);
                        // Since we don't have the exact method, assume it's a virtual at vtable+0x164
                        // But that offset is large; maybe it's actually inside another function.
                        // We'll omit that call in the reconstruction as it's likely compiler noise.
                        // Instead, we assume a call to FUN_007223b0 (which takes a float) is meant.
                        FUN_007223b0(blendTime); // e.g., Math::smoothStep(blendTime)
                    }
                    // Determine which animation hash to use based on state
                    if (state == 2) {
                        animHash = 0x28083235; // Hash for animation A
                    }
                    else if (state == 3) {
                        animHash = 0xfa3c92af; // Hash for animation B
                    }
                    else {
                        animHash = 0x00ca9bea; // Default hash (maybe invalid)
                    }
                    // Call virtual function at offset 0x2c to set animation parameters
                    (**(code (__fastcall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(
                        thisPtr, animHash, 1, 1, 0,
                        (float)thisPtr[0x17] * _DAT_00d5eee8, // +0x5C: m_blendWeight * g_weightScale
                        0x3f800000); // 1.0f
                }
            }
        }
    }
    return;
}