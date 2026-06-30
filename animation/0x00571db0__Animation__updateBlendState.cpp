// FUNC_NAME: Animation::updateBlendState

void Animation::updateBlendState() {
    // +0x110: blendState (0 = idle, 1 = blending in, -1 = blending out?)
    int blendState = *(int*)(this + 0x110);
    if (blendState != 0) {
        if (blendState < 1) {
            // Negative blend state (e.g., blending out)
            // +0x114: blendTime (int, interpreted as float)
            // _DAT_00e446b8: timeScale factor?
            float scaledTime = g_BlendThreshold - (float)(*(int*)(this + 0x114)) * g_TimeScaleFactor;
            if (scaledTime > 0.0f) {
                double d = (double)(scaledTime * g_BlendSpeedMultiplier);
                debugPrint(); // FUN_00b99fcb - likely a console print
                scaledTime = (float)d;
            }
            if (scaledTime <= 0.0f) {
                *(int*)(this + 0x110) = 0;
                *(byte*)(this + 0x121) = 0; // +0x121: blendFinished flag
                // Virtual call at vtable+4 (e.g., onBlendComplete)
                (*(void (__thiscall**)(Animation*))(*(int*)this + 4))(this);
            }
        } else {
            // Positive blend state (blending in)
            float currentTime = (float)*(int*)(this + 0x114);
            // +0x118: blendDuration (int, interpreted as float)
            float duration = (float)*(int*)(this + 0x118);
            if (duration == 0.0f) {
                *(int*)(this + 0x110) = 0;
                return;
            }
            float progress = currentTime / duration;
            if (progress < g_BlendThreshold) {
                double d = (double)(progress * g_BlendSpeedMultiplier);
                debugPrint();
                progress = (float)d;
            }
            if (g_BlendThreshold <= progress) {
                *(int*)(this + 0x110) = 0;
                return;
            }
        }
    }
}