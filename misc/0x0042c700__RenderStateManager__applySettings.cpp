// FUNC_NAME: RenderStateManager::applySettings
// Function address: 0x0042c700
// This function applies rendering state settings based on incoming flags and internal state.
// It clamps global rendering parameters, sets D3D render states, and calls virtual methods on sub-objects.

void RenderStateManager::applySettings(uint flags)
{
    bool bVar1;
    bool bVar2;
    uint processedFlags;
    void (*callback)();

    // Initialization call
    initializeSubsystem(this->m_field0xe7e); // +0xe7e

    // Check global flag and adjust param_1
    if (((&globalFlagArray)[this->m_field0xe7e == 0] == 0) || (this->m_field0xe7e == 1)) {
        processedFlags = globalModeSetting;
    } else {
        processedFlags = 1;
    }

    // Clamp global render state variables to range [0x38, 0x3a]
    if (g_renderStateMin < 0x38) { g_renderStateMin = 0x38; }
    if (0x38 < g_renderStateMax) { g_renderStateMax = 0x38; }
    g_renderStateA = 8; // D3DRS_FILLMODE = D3DFILL_SOLID
    if (g_renderStateMin < 0x39) { g_renderStateMin = 0x39; }
    if (0x39 < g_renderStateMax) { g_renderStateMax = 0x39; }
    g_renderStateB = (uint)(~(byte)(flags >> 4) & 0x40 | 0x21);
    if (g_renderStateMin < 0x3a) { g_renderStateMin = 0x3a; }
    if (0x3a < g_renderStateMax) { g_renderStateMax = 0x3a; }
    g_renderStateC = 0xe0; // D3DRS_CULLMODE = D3DCULL_CW

    // Determine sub-state based on flags and internal counters
    uint frameFlags = this->m_frameFlags; // +0xebe
    if (((((uint)frameFlags >> 4 & 1) == 0) || ((flags & 0x200) == 0)) || (g_globalFlag == '\0') || (this->m_field0xe7e == 1)) {
        bVar1 = false;
    } else {
        bVar1 = true;
    }

    if (((((uint)frameFlags >> 4 & 1) == 0) && ((flags & 0x400) != 0)) &&
       ((g_globalFlag != '\0' && (this->m_field0xe7e != 1)))) {
        bVar2 = true;
    } else {
        bVar2 = false;
    }

    g_renderStateB = processedFlags;
    if (bVar1 || bVar2) {
        // Call virtual method on sub-object at offset this[*this + 10]
        int* subObject = (int*)this[*(int*)this + 10];
        (**(code **)(*(int*)subObject + 0x18))(subObject, 2);
    }

    // Apply state to a sub-structure at +0x48c
    applyStateToSubObject((int*)this + 0x48c, processedFlags, 0, flags);
    resetState(0, flags);

    if (this->m_field0xe7e != 1) {
        // Repeat clamping (likely redundant due to compiler optimization)
        if (g_renderStateMin < 0x38) { g_renderStateMin = 0x38; }
        if (0x38 < g_renderStateMax) { g_renderStateMax = 0x38; }
        g_renderStateA = 8;
        if (g_renderStateMin < 0x39) { g_renderStateMin = 0x39; }
        if (0x39 < g_renderStateMax) { g_renderStateMax = 0x39; }
        g_renderStateB |= 0x80;
        if (g_renderStateMin < 0x3a) { g_renderStateMin = 0x3a; }
        if (0x3a < g_renderStateMax) { g_renderStateMax = 0x3a; }
        callback = nullptr;
        g_renderStateC = 0xffffffff; // D3DRS_ZENABLE = FALSE
        if (g_alternateFlag != '\0') {
            callback = alternateRenderCallback; // FUN_00428d90
        }
        applyStateToDevice(this, processedFlags, 0, (int*)this + 0x634, 0, callback);
        if (bVar1 || bVar2) {
            // Call virtual method again with different arg
            int* subObject = (int*)this[*(int*)this + 10];
            (**(code **)(*(int*)subObject + 0x18))(subObject, 1);
        }
        // Final clamping and state setting (redundant)
        if (g_renderStateMin < 0x38) { g_renderStateMin = 0x38; }
        if (0x38 < g_renderStateMax) { g_renderStateMax = 0x38; }
        g_renderStateA = 8;
        if (g_renderStateMin < 0x39) { g_renderStateMin = 0x39; }
        if (0x39 < g_renderStateMax) { g_renderStateMax = 0x39; }
        if (g_renderStateMin < 0x3a) { g_renderStateMin = 0x3a; }
        if (0x3a < g_renderStateMax) { g_renderStateMax = 0x3a; }
        g_renderStateC = 0xffffffff;
        g_renderStateB = processedFlags;
    }
    return;
}