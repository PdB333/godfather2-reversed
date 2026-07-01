// FUNC_NAME: StreamManager::processUpdate
void __thiscall StreamManager::processUpdate(ushort updateFlags)
{
    char isValid;
    int *currentList;
    int count;
    int idx;

    // Store the update flags at +0x100 (bitmask controlling sub-updates)
    m_updateFlags = updateFlags;

    // Conditionally update sub-lists based on flags
    if ((m_updateFlags & 0x01) == 0) {
        updateActiveList();     // FUN_0097cd60
    }
    if ((m_updateFlags >> 1 & 0x01) == 0) {
        updatePendingList();    // FUN_0097ce70
    }
    if ((m_updateFlags >> 2 & 0x01) == 0) {
        updateLoadedList();     // FUN_0097cf90
    }

    // Remove invalid entries from current list (array at +0x7c, count at +0x9c)
    count = m_currentCount;         // +0x9c
    if (count != 0) {
        // Start from the last element (array base +0x7c, but pointer arithmetic uses +0x78 as base)
        currentList = &m_currentList[count]; // After last element, will decrement
        idx = count;
        do {
            idx--;
            // Check if the current element is still valid
            isValid = isElementValid(*currentList); // FUN_0097b920
            if (isValid == false) {
                // Remove element: decrement count and swap with last if not already last
                m_currentCount = m_currentCount - 1;
                if (idx != m_currentCount) {
                    *currentList = m_currentList[m_currentCount];
                }
                // After removal, check if all counts are zero -> shutdown condition
                if (m_loadedCount + m_pendingCount + m_activeCount + m_currentCount == 0) {
                    onAllQueuesEmpty(); // FUN_0097c5d0
                }
                // If current list becomes empty, call global resource finalizer
                if (m_currentCount == 0) {
                    finalizeResourceSystem(&g_resourceData); // FUN_004086d0(&DAT_0112a638)
                }
            }
            count--;
            currentList--;
        } while (count != 0);
    }
}