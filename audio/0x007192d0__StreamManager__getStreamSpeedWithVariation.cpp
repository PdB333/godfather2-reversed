// FUNC_NAME: StreamManager::getStreamSpeedWithVariation

float __fastcall StreamManager::getStreamSpeedWithVariation(void* this) {
    int trackState = *(int*)(*(int*)((char*)this + 0x18) + 0x2004); // +0x18 -> internal data pointer, +0x2004 -> track/state index
    if ((trackState != 0) && (trackState != 0x48)) {
        // Apply random speed variation if track is active and not in a specific state (0x48 = paused?)
        return FUN_007234c0(0); // returns a random float (e.g., 0.8-1.2)
    }
    // Return default speed (constant)
    return *(float*)0x00d5f378; // default speed, usually 1.0f
}