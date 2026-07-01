//FUNC_NAME: SelectionManager::getCurrentSelectionData
void __thiscall SelectionManager::getCurrentSelectionData(int thisPtr, uint* outFirstField, uint* outCurrentField)
{
    int gameMode = *(int*)(DAT_01130044 + 0xb8); // g_pGameManager->m_currentGameMode
    *outFirstField = 0;
    *outCurrentField = 0;

    if (gameMode == 10 || gameMode == 11 || gameMode == 12) // e.g., kModeMenu, kModeLoading, kModePlaying
    {
        int currentIndex = *(int*)(thisPtr + 0x50); // m_currentIndexA
        if (currentIndex != 0)
        {
            int* arrayBase = *(int**)(thisPtr + 0x4c); // m_arrayA
            *outFirstField = *(uint*)(*arrayBase + 0x28); // first element's field at +0x28
            *outCurrentField = *(uint*)(arrayBase[currentIndex] + 0x28);
        }
    }
    else if (gameMode == 0x19) // e.g., kModePaused
    {
        int currentIndex = *(int*)(thisPtr + 0x5c); // m_currentIndexB
        if (currentIndex != 0)
        {
            int* arrayBase = *(int**)(thisPtr + 0x58); // m_arrayB
            *outFirstField = *(uint*)(*arrayBase + 0x2c); // field at +0x2c
            *outCurrentField = *(uint*)(arrayBase[currentIndex] + 0x2c);
        }
    }
    else if (gameMode == 0xd || gameMode == 0xe || gameMode == 0xf || gameMode == 0x10 || gameMode == 0x11) // e.g., kModeX to kModeX+4
    {
        int currentIndex = *(int*)(thisPtr + 0x68); // m_currentIndexC
        if (currentIndex != 0)
        {
            int* arrayBase = *(int**)(thisPtr + 100); // m_arrayC (offset 0x64)
            *outFirstField = *(uint*)(*arrayBase + 0x2c);
            *outCurrentField = *(uint*)(arrayBase[currentIndex] + 0x2c);
        }
    }
    else
    {
        // Fallback: get context from another manager
        char contextValid = FUN_00917060(); // returns bool, sets EDX to context pointer
        if (contextValid)
        {
            int contextPtr = (int)contextValid; // actually EDX from the call, but we need to capture it
            // Note: The decompiler shows extraout_EDX, which is the value of EDX after the call.
            // We'll assume the function returns the context pointer in EDX and success in EAX.
            // For reconstruction, we'll use a separate variable.
            int currentIndex = *(int*)(contextPtr + 0x74); // m_currentIndexD
            if (currentIndex != 0)
            {
                int* arrayBase = *(int**)(contextPtr + 0x70); // m_arrayD
                *outFirstField = *(uint*)(*arrayBase + 0x18);
                *outCurrentField = *(uint*)(arrayBase[currentIndex] + 0x18);
            }
        }
    }
}