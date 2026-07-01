// FUNC_NAME: MasterScaleController::applyScale
void __thiscall MasterScaleController::applyScale(int this, float scaleFactor) {
    // Skip if scaleFactor is the sentinel value (likely 1.0f indicating no change)
    if (scaleFactor != g_SentinelFloat) {
        // Update master scale: multiply current by incoming factor
        float newMasterScale = *(float *)(this + 0x184) * scaleFactor;
        // Compute the value to propagate to children
        float appliedValue = *(float *)(this + 0x144) * newMasterScale;
        // Store new master scale
        *(float *)(this + 0x184) = newMasterScale;

        // Clamp: if appliedValue became negative, reset to base scale
        if (appliedValue < 0.0f) {
            appliedValue = *(float *)(this + 0x144);
        }

        // Propagate appliedValue to first set of child objects
        uint childCount1 = *(uint *)(this + 0x118);
        if (childCount1 != 0) {
            uintptr_t* childList1 = *(uintptr_t **)(this + 0x114);
            for (uint i = 0; i < childCount1; i++) {
                // Each child has a float at offset 0x80 (e.g., volume, speed, intensity)
                *(float *)(childList1[i] + 0x80) = appliedValue;
            }
        }

        // Propagate appliedValue to second set of child objects
        uint childCount2 = *(uint *)(this + 0x10c);
        if (childCount2 != 0) {
            uintptr_t* childList2 = *(uintptr_t **)(this + 0x108);
            for (uint i = 0; i < childCount2; i++) {
                *(float *)(childList2[i] + 0x80) = appliedValue;
            }
        }
    }
}