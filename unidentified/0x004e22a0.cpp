// FUN_004e22a0: InputManager::storeInputSnapshotToGlobalBuffer
void __thiscall InputManager::storeInputSnapshotToGlobalBuffer(uint32_t* sourceA, uint32_t* sourceB)
{
    // Global debug buffer for input snapshots at 0x01218d40 (48 uint32s)
    extern uint32_t g_inputSnapshotBuffer[48];

    // Copy param_2 (sourceB) to buffer[0..15]
    for (int i = 0; i < 16; i++)
        g_inputSnapshotBuffer[i] = sourceB[i];

    // Copy param_1 (sourceA) to buffer[16..31]
    for (int i = 0; i < 16; i++)
        g_inputSnapshotBuffer[16 + i] = sourceA[i];

    // Copy this->m_data to buffer[32..47] (this pointer holds the third 16-dword array)
    for (int i = 0; i < 16; i++)
        g_inputSnapshotBuffer[32 + i] = this->m_data[i];

    // Process the captured snapshot (e.g., write to log)
    processDebugSnapshot();
}