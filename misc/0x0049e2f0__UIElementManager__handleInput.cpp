// FUNC_NAME: UIElementManager::handleInput

int UIElementManager::handleInput(uint* pList, int elementIndex, uint inputFlags)
{
    uint* currentList = pList;
    int result = 1; // Default return value

    if (pList != nullptr)
    {
        // Get pointer to the UI element from the list
        int* pElement = reinterpret_cast<int*>(pList[elementIndex * 2 + 2]);
        if (pElement != nullptr)
        {
            // If the active element changed, finalize previous and initialize new
            if (g_pCurrentActiveElement != pElement)
            {
                if (g_pCurrentActiveElement != nullptr)
                {
                    // Call finalize on previous element (vtable+0x20)
                    reinterpret_cast<void(__thiscall*)(void*)>(*(uint*)g_pCurrentActiveElement + 0x20)(g_pCurrentActiveElement);
                }
                // Call initialize on new element (vtable+0x18)
                reinterpret_cast<void(__thiscall*)(void*)>(*(uint*)pElement + 0x18)(pElement);
                result = 2; // Return 2 to indicate active element changed
            }

            uint combinedFlags = *pList & inputFlags;
            // Store current list globally
            g_pCurrentUIList = pList;

            if (combinedFlags != 0)
            {
                // Handle individual flag bits
                if ((combinedFlags & 1) != 0) // Bit 0
                {
                    // Set some global limits
                    if (g_globalMin < 25) g_globalMin = 25;
                    if (g_globalMax > 25) g_globalMax = 25;
                    g_globalSetting1 = 7;
                    if (g_globalMin < 24) g_globalMin = 24;
                    if (g_globalMax > 24) g_globalMax = 24;
                    g_globalSetting2 = 0x80;
                    if (g_globalMin < 15) g_globalMin = 15;
                    if (g_globalMax > 15) g_globalMax = 15;
                    g_globalSetting3 = 1;
                }
                else if ((combinedFlags & 0x20) != 0) // Bit 5
                {
                    showDialog(2, 5, 1, 1, 5);
                }
                else if ((combinedFlags & 0x40) != 0) // Bit 6
                {
                    playSound(3, 5, 2);
                }
                else if ((combinedFlags & 0x100) != 0) // Bit 8
                {
                    startAnimation(1);
                    showDialog(5, 6, 1, 14, 6);
                    // Use some parameter from list and global
                    uint adjustedParam = (uint)((float)pList[1] * g_someFloat) & 0xFF;
                    setColor(adjustedParam, adjustedParam, adjustedParam, adjustedParam);
                    goto afterFlagCheck;
                }
                else if (static_cast<char>(combinedFlags) < 0) // Bit 7 (signed check)
                {
                    playSound(1, 5, 2);
                }
            }

afterFlagCheck:
            // Check if high bits (0x30000) are set and bit 0 is set in list flags
            if (((inputFlags & 0x30000) != 0) && ((*pList & 1) != 0))
            {
                if (g_globalMin < 22) g_globalMin = 22;
                if (g_globalMax > 22) g_globalMax = 22;
                g_globalSetting4 = 1;
            }

            // If the element's flag is zero, perform update
            if (pList[elementIndex * 2 + 3] == 0)
            {
                updateElementState();
            }

            return result;
        }
    }
    return 0;
}