// FUNC_NAME: ColorManager::setColorSlot
// Function at 0x0060add0: Sets a 4-float color/property slot in one of two global color tables (day/night or similar) and notifies the manager.
// Table selection: if high bit set in slotIndex, use ambientColorTable (0x011ea8f0), else use sunColorTable (0x011d97f0).
// Slot index is low 8 bits of slotIndex.
// After copying, if any component changed, calls manager's notification vtable function (0x178 for ambient, 0x1b4 for sun) to propagate the change.

// Global manager singleton pointer
extern ColorManager* g_ColorManager; // 0x01205750

// Global color tables (size: 256 entries of 4 floats each)
extern float g_sunColorTable[256][4]; // 0x011d97f0
extern float g_ambientColorTable[256][4]; // 0x011ea8f0

// Vtable offsets for notification (likely member functions)
// At vtable+0x178: void onAmbientSlotChanged(); // no args
// At vtable+0x1b4: void onSunSlotChanged(uint slotIndex, float* slotData, int syncFlag);

void ColorManager::setColorSlot(uint slotIndex, float* colorVector) {
    if (slotIndex == 0) return;

    uint index = slotIndex & 0xFF;
    float* slotPtr;

    // Choose table based on sign bit of slotIndex
    if ((int)slotIndex >= 0) {
        slotPtr = g_sunColorTable[index];
    } else {
        slotPtr = g_ambientColorTable[index];
    }

    // Copy each component only if different (optimization)
    bool changed = false;
    if (slotPtr[0] != colorVector[0]) {
        slotPtr[0] = colorVector[0];
        changed = true;
    }
    if (slotPtr[1] != colorVector[1]) {
        slotPtr[1] = colorVector[1];
        changed = true;
    }
    if (slotPtr[2] != colorVector[2]) {
        slotPtr[2] = colorVector[2];
        changed = true;
    }
    if (slotPtr[3] != colorVector[3]) {
        slotPtr[3] = colorVector[3];
        changed = true;
    }

    if (changed) {
        // Notify manager based on table type
        if ((int)slotIndex < 0) {
            // Ambient table changed: call vtable+0x178
            (g_ColorManager->*((void(*)())(*(uint*)g_ColorManager + 0x178)))();
        } else {
            // Sun table changed: call vtable+0x1b4 with parameters
            (g_ColorManager->*((void(*)(void*, uint, float*, int))(*(uint*)g_ColorManager + 0x1b4)))(g_ColorManager, index, slotPtr, 1);
        }
    }
}