// FUNC_NAME: VFXManager::executeQueuedEffect
// Address: 0x005312d0
void __thiscall VFXManager::executeQueuedEffect(VFXManager* this) {
    if (g_bPendingEffect) { // Global flag indicating a queued effect is ready
        uint32_t effectIndex = *(uint32_t*)(this + 0x16C); // +0x16C: m_queuedEffectIndex
        EffectData* effectData = nullptr;
        if (effectIndex < 0x1000) {
            // g_effectDataTable is a global array of 0x38-byte EffectData entries
            effectData = &g_effectDataTable[effectIndex];
        }
        // spawnEffect with parameters from the effect data
        // Uses two half-float (ushort) fields from the effect data for X/Y position
        // Other parameters come from globals and constants (scale 1.0, 1.0)
        spawnEffect(this,
                    0,
                    0,
                    (float)(*(uint16_t*)((uint32_t)effectData + 2)), // +0x02: positionX half-float
                    (float)(*(uint16_t*)((uint32_t)effectData + 4)), // +0x04: positionY half-float
                    &g_effectTransform,   // Global transform/matrix
                    g_effectParam1,       // Global float parameter 1
                    g_effectParam2,       // Global float parameter 2
                    0,
                    0,
                    1.0f,
                    1.0f);
        g_bPendingEffect = 0; // Clear flag after execution
    }
}