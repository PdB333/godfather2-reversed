// Xbox PDB: EARS_Apt_UIHudMultiplayer_UpdateCaptureTimer
// FUNC_NAME: CrimeScene::updateCaptureTimer
void __thiscall CrimeScene::updateCaptureTimer(float rateA, float rateB, float totalTime)
{
    // Global constants and frame delta time (from EARS engine)
    extern const float kMaxCaptureProgress;   // DAT_00d5e288: maximum capture progress (e.g., 100.0f)
    extern const float g_frameDeltaTime;      // _DAT_00d5780c: time elapsed since last frame (seconds)

    // Calculate progress delta for both sides
    float progressDeltaA = (g_frameDeltaTime / totalTime) * rateA * kMaxCaptureProgress;
    float progressDeltaB = (g_frameDeltaTime / totalTime) * rateB * kMaxCaptureProgress;

    // Clamp progress A to [0, max]
    if (progressDeltaA >= 0.0f) {
        if (progressDeltaA > kMaxCaptureProgress) {
            progressDeltaA = kMaxCaptureProgress;
        }
    } else {
        progressDeltaA = 0.0f;
    }

    // Clamp progress B to [0, max]
    if (progressDeltaB >= 0.0f) {
        if (progressDeltaB > kMaxCaptureProgress) {
            progressDeltaB = kMaxCaptureProgress;
        }
    } else {
        progressDeltaB = 0.0f;
    }

    // Store updated progress values at object offsets +0x88 and +0x8c
    *(float *)((char *)this + 0x88) = progressDeltaA;  // m_captureProgressA
    *(float *)((char *)this + 0x8c) = progressDeltaB;  // m_captureProgressB

    // Debug/performance logging (FUN_005a04a0 is likely a profiler event tracker)
    FUN_005a04a0("UpdateCaptureTimer", 0, &DAT_00d8b7d4, 0);
}