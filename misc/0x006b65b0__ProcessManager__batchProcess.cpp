// FUNC_NAME: ProcessManager::batchProcess
void __fastcall ProcessManager::batchProcess(ProcessManager* thisObj) {
    // +0x78: batch mode flag (0 = fixed count mode, non-zero = array mode)
    if (thisObj->m_batchMode == 0) {
        // Fixed count mode: process m_remainingCount items
        for (int i = thisObj->m_remainingCount; i != 0; i--) {
            // Process item index 0 each time? Actually FUN_006b5c50(0) is called, maybe it uses a separate counter? 
            // But the same index 0 is passed repeatedly. Possibly processNextItem().
            thisObj->processItem(0);  // Likely processes the next item in an internal list
            thisObj->m_processedCount++;

            // Check if time budget exceeded (global float at 0x00d577a0) or force update flag
            // +0x80: time budget threshold (float)
            // +0x34: flags, bit 29 = 0x20000000 (force update)
            if ((g_globalTime > thisObj->m_timeBudget) || ((thisObj->m_flags >> 29) & 1)) {
                thisObj->processFullBudget();
            } else {
                thisObj->processPartialBudget();
            }
        }
    } else {
        // Array mode: iterate over m_itemArray of size m_itemCount (from end to start)
        int idx = thisObj->m_itemCount - 1;
        if (idx >= 0) {
            do {
                int item = thisObj->m_itemArray[idx];  // +0xa8: array pointer, +0xac: count
                if (thisObj->isItemValid(item)) {  // FUN_00791230 returns bool
                    thisObj->processItem(item);
                    thisObj->m_processedCount++;
                    if ((g_globalTime > thisObj->m_timeBudget) || ((thisObj->m_flags >> 29) & 1)) {
                        thisObj->processFullBudget();
                    } else {
                        thisObj->processPartialBudget();
                    }
                }
                idx--;
            } while (idx >= 0);
        }
    }
}