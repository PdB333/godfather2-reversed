// FUNC_NAME: DebugOverlayData::updateFromGameState
void __thiscall DebugOverlayData::updateFromGameState(void)
{
    // Get camera manager (likely CameraManager::getInstance)
    int cameraMgr = FUN_0059c810();
    // Get the entity the camera is following (player or target)
    int* targetEntity = *(int**)(cameraMgr + 8);

    // Get entity data manager (likely EntityDataManager::getInstance)
    int entityDataMgr = FUN_0059c3b0();
    // Chain: entityDataMgr + 0x58 -> pointer, +8 -> pointer, +4 -> some value (e.g., type array base)
    int entityTypeArrayBase = *(int*)(*(int*)(*(int*)(entityDataMgr + 0x58) + 8) + 4);

    // Copy fields into internal buffer (indices in m_data)
    // Target entity fields:
    m_data[0xb] = *(int*)(targetEntity + 0x2c); // +0x2c: some status/health
    m_data[0xc] = *(int*)(targetEntity + 0x30); // +0x30
    m_data[5] = *(int*)(targetEntity + 0x1c);   // +0x1c
    m_data[0x14] = *(int*)(targetEntity + 0x24); // +0x24
    m_data[1] = *(int*)(targetEntity + 8);       // position X
    m_data[2] = *(int*)(targetEntity + 0xc);     // position Y (or Z)

    // Camera manager fields:
    m_data[6] = *(int*)(cameraMgr + 0x40);       // +0x40
    m_data[0xd] = *(int*)(cameraMgr + 0x24);     // +0x24
    m_data[0x15] = *(int*)(cameraMgr + 0x2c);    // +0x2c
    m_data[0xe] = *(int*)(cameraMgr + 0x38);     // +0x38
    m_data[0xf] = *(int*)(cameraMgr + 0x3c);     // +0x3c
    m_data[0x10] = *(int*)(cameraMgr + 0x34);    // +0x34
    m_data[0x11] = *(int*)(cameraMgr + 0x30);    // +0x30
    // Note: index 3 and 4 are derived from camera, simplified to direct read
    m_data[3] = *(float*)(cameraMgr + 0x4c);     // +0x4c
    m_data[4] = *(float*)(cameraMgr + 0x50);     // +0x50

    // First element depends on target entity's type index
    if (*(int*)(targetEntity + 0x18) < 0) {
        m_data[0] = 0;
    } else {
        // entityTypeArrayBase + 0x18 is an array of pointers to type data
        // index by targetEntity->0x18 (type index)
        int* typeEntryPtr = *(int**)(entityTypeArrayBase + 0x18 + *(int*)(targetEntity + 0x18) * 4);
        m_data[0] = *(int*)(typeEntryPtr + 8); // +8: some property
    }

    // Zero out unused slots
    m_data[0x17] = 0;
    m_data[0x18] = 0;
}