// FUNC_NAME: EventScheduler::popNextEvent
int* __fastcall EventScheduler::popNextEvent(int thisPtr)
{
    int* pCurrent = *(int**)(thisPtr + 0x37C08); // m_pCurrentWorkingJob
    // Check if there's a current job and if the system is not in a "locked" state (0x90)
    if (((pCurrent != (int*)0x0) &&
        (*(int*)(thisPtr + 0x43080) != 0x90)) && // m_SomeFlag1
        (*(short*)(thisPtr + 0x43088) != 0x90)) // m_SomeFlag2
    {
        // Advance to next working job (removing current? or just skip?)
        *(int**)(thisPtr + 0x37C08) = (int*)pCurrent[0x10]; // m_pCurrentWorkingJob = pCurrent->next
        return pCurrent;
    }

    int pNode = *(int*)(thisPtr + 4);  // m_pJobListHead
    int bestNode = 0;
    float bestPriority = DAT_00e2eff4; // Global constant, likely -FLT_MAX

    if (pNode != *(int*)(thisPtr + 0xC)) // m_pJobListTail sentinel
    {
        do
        {
            float priority = DAT_00e2eff4;
            int* pData = *(int**)(pNode + 0x20); // JobData pointer
            int* pDataEnd = *(int**)(pNode + 0x28); // End of data? Maybe sentinel
            if (pData != pDataEnd)
            {
                priority = *(float*)(pData + 0x14); // JobData::priority (+0x54? actually pData is int* so +0x14*4=0x50? Wait: char? No, pData is int*, so pData[0x14] is at offset 0x50 bytes. But code says *(int*)(pData+0x14) interpreted as float. So priority field at offset 0x50 from JobData. We'll document.
            }
            if (bestPriority < priority)
            {
                bestNode = pNode;
                bestPriority = priority;
            }
            pNode = *(int*)(pNode + 0x2C); // m_pNext in node
        } while (pNode != *(int*)(thisPtr + 0xC)); // m_pJobListTail
    }

    if ((bestNode != 0) &&
        (int* pJob = *(int**)(bestNode + 0x20), pJob != *(int**)(bestNode + 0x28)))
    {
        // Remove pJob from doubly linked list
        // pJob[0x10] = prev, pJob[0x11] = next? Actually offsets are 0x40 and 0x44 from node? No, pJob is the data pointer, not the node. Code uses piVar1[0x10] and piVar1[0x11] where piVar1 is the job data. So the job data itself has prev and next at offsets 0x40 and 0x44.
        *(int*)(pJob[0x11] + 0x40) = pJob[0x10]; // next->prev = this
        *(int*)(pJob[0x10] + 0x44) = pJob[0x11]; // prev->next = this
        if (pJob[0x34] != 0) // Some flag, maybe m_bRequiresCleanup
        {
            FUN_0066dfe0(); // Cleanup function (e.g., Job::destroy)
            pJob[0x34] = 0; // Clear flag
        }
        // Call virtual method at vtable+4 (e.g., Job::start)
        (**(void (__thiscall**)(int*))(*pJob + 4))(pJob);
        return pJob;
    }

    return (int*)0x0; // No job found
}