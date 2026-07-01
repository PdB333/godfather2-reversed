// FUNC_NAME: TargetingManager::getBestTargetIndex
// Function address: 0x008b5310

uint __thiscall TargetingManager::getBestTargetIndex()
{
    int bestValue;
    uint bestIndex;

    // Check if a global target override is active and valid
    if (g_pTargetingManager != nullptr && g_pTargetingManager->m_forcedTargetIndex != -1)
    {
        // Return 1 if forced target is index 0, else 0
        // This boolean might indicate whether to force the first target
        return (uint)(g_pTargetingManager->m_forcedTargetIndex == 0);
    }

    bestValue = 0;
    bestIndex = -1; // 0xFFFFFFFF, indicates no best found yet

    // Evaluate first target if any exist
    if (m_targetCount != 0) // +0x1b0
    {
        bestValue = getTargetPriority(0); // FUN_008b4e20(0)
        bestIndex = 0;
    }

    // Loop through remaining targets to find the one with highest priority
    for (uint i = 1; i < m_targetCount; i++) // +0x1b0 unsigned
    {
        int currentValue = getTargetPriority(i); // FUN_008b4e20(i)
        if (currentValue > bestValue)
        {
            bestValue = currentValue;
            bestIndex = i;
        }
    }

    return bestIndex;
}