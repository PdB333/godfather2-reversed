// FUNC_NAME: GlobalStateManager::copyAndNotify
void __fastcall GlobalStateManager::copyAndNotify(unsigned int* pData)
{
    // Copy 16 DWORDs from input to global state buffer
    // g_globalData is at 0x01219b50 (64 bytes)
    g_globalData[0] = pData[0];
    g_globalData[1] = pData[1];
    g_globalData[2] = pData[2];
    g_globalData[3] = pData[3];
    g_globalData[4] = pData[4];
    g_globalData[5] = pData[5];
    g_globalData[6] = pData[6];
    g_globalData[7] = pData[7];
    g_globalData[8] = pData[8];
    g_globalData[9] = pData[9];
    g_globalData[10] = pData[10];
    g_globalData[11] = pData[11];
    g_globalData[12] = pData[12];
    g_globalData[13] = pData[13];
    g_globalData[14] = pData[14];
    g_globalData[15] = pData[15];

    // Condition: activeManager (0x012058e8) points to the global manager instance (0x01219a70)
    // and the handler at index g_currentIndex (0x01219b20) in the handler array (0x01219cb0, stride 0x30) is non-null
    if (g_activeManagerPtr == &g_manager && 
        g_handlerArray[g_currentIndex].handlerPtr != nullptr)
    {
        // Notify the registered handler with manager context and the original data
        FUN_0060b020(g_managerContext, g_handlerArray[g_currentIndex].handlerPtr, pData);
    }
}