// FUNC_NAME: JobManager::processJobActivation
bool __fastcall JobManager::processJobActivation(int unused, JobManager* pManager) {
    // +0x14: m_bReady (bool, 0 = ready to activate a job)
    bool bReady = pManager->m_bReady == 0; // Check if manager is ready for activation

    if (bReady && (bReady = g_pActiveJob != nullptr, bReady)) {
        // +0x1c: m_pJobListHead (linked list of JobNode)
        // Node layout:
        //   +0x4: m_bBlocked (bool, non-zero = activation blocked)
        //   +0x14: m_pJobId (void* or ID pointer, matches global)
        //   +0xc: m_pNext
        bool found = false;
        JobNode* pNode = pManager->m_pJobListHead;
        while (pNode != nullptr) {
            if (pNode->m_pJobId == g_pActiveJob) {
                // If the job's blocked flag is non-zero, return immediately false
                if (pNode->m_bBlocked != 0) {
                    return false;
                }
                // Call an external function to actually activate the job
                bool success = (bool)FUN_00650370();
                return success;
            }
            pNode = pNode->m_pNext;
        }
        // Job not found in list – return false
        return false;
    }
    // Not ready or no active job to process
    return bReady;
}