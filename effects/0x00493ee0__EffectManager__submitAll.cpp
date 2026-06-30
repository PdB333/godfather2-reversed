// FUNC_NAME: EffectManager::submitAll
void EffectManager::submitAll() {
    // Begin frame submission (likely state reset)
    FUN_00490b20();

    // Check if primary effect slot is active (flag at +0x1c0)
    if (m_primaryEffectActive) {
        // Submit primary effect: device (+0x14), effect data (+0x1c0), output buffer (+0x1d0)
        FUN_0060ad20(m_renderDevice, m_primaryEffectData, &m_primaryEffectBuffer);
    }

    // End primary submission (sync / finalize)
    FUN_00492190();

    // Submit effect slot 3: data at +0x2d4, buffer at +0x2e0
    FUN_0060ad20(m_renderDevice, m_effectSlot3Data, &m_effectSlot3Buffer);
    // Submit effect slot 4: data at +0x2f0, buffer at +0x300 (uses different submit variant)
    FUN_0060add0(m_renderDevice, m_effectSlot4Data, &m_effectSlot4Buffer);
    // Set effect parameters for slot 5: two data values at +0x310 and +0x314
    FUN_0060aa90(m_renderDevice, m_effectParam1, m_effectParam2);
    // Submit effect slot 6: data at +0x318, buffer at +0x330
    FUN_0060b020(m_renderDevice, m_effectSlot6Data, &m_effectSlot6Buffer);
    // Submit effect slot 7: data at +0x31c, buffer at +0x370
    FUN_0060b020(m_renderDevice, m_effectSlot7Data, &m_effectSlot7Buffer);
    // Submit effect slot 8: data at +0x320 (800 decimal), buffer at +0x3b0
    FUN_0060b020(m_renderDevice, m_effectSlot8Data, &m_effectSlot8Buffer);
    // Submit effect slot 9: data at +0x3f0, buffer at +0x400
    FUN_0060add0(m_renderDevice, m_effectSlot9Data, &m_effectSlot9Buffer);
}