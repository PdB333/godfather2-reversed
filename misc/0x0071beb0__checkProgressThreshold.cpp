// FUNC_NAME: checkProgressThreshold
bool __thiscall checkProgressThreshold(void* this) {
    // +0x24: progress value (e.g., timer, distance, or accumulated)
    float progress = *(float*)((char*)this + 0x24);

    // Global threshold constant (likely a positive maximum)
    if (progress >= 0.0f && progress >= DAT_01205228) {
        return false; // threshold reached or exceeded
    }
    return true; // still below threshold
}