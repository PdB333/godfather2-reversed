// FUNC_NAME: Presentation::submitIfVisible
// Function address: 0x006f2220
bool Presentation::submitIfVisible(int param3, int param4, uint param5) {
    // Global checks: pause and cutscene status
    if (IsGamePaused()) {
        return false;
    }
    if (IsCutsceneActive()) {
        return false;
    }

    // Ensure this object has valid model data
    // +0x10: pModelData (void*)
    if (this->pModelData == nullptr) {
        return false;
    }

    // Build drawing flags: bit 2 forced if isForcedVisible set
    // +0x14: isForcedVisible (char, 0 or 1)
    uint drawFlags = (this->isForcedVisible ? 0x4 : 0x0) | param5;

    // Submit the draw call
    // FUN_006f77a0 -> RenderSubmit(submitType=0, data, param4, param3, drawFlags, 0, 0)
    bool result = RenderSubmit(0, this->pModelData, param4, param3, drawFlags, 0, 0);
    return result;
}