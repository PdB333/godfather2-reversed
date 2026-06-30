// FUNC_NAME: ObjectiveManager::UpdateActiveObjectiveList
void ObjectiveManager::UpdateActiveObjectiveList(void)
{
    int *pManager = (int *)DAT_0122339c;       // Global pointer to objective manager instance
    int *pContext = *(int **)(__readfsdword(0x2c)); // Thread-local context pointer (FS:[0x2c])
    char activeCount = '\0';

    DAT_01162387 = '\0';                        // Clear global active objective count

    if ((pManager != (int *)0x0) && (DAT_012233a0 != (int)0x0))   // Check manager and flag
    {
        int objCount = *(int *)(pManager + 0x55); // +0x154: Number of objective slots
        if (0 < objCount)
        {
            int *pSlot = (int *)(pManager + 0x56); // +0x158: Start of objective slot array
            do
            {
                int objId;
                if (*(int *)(pManager + 0x55) == 0)  // This condition is always false here (count != 0)
                {
                    objId = *(int *)(*pContext + 9); // +0x24: Objective from thread context
                }
                else
                {
                    objId = *(int *)(pManager + 0x5); // +0x14: Main objective ID from manager
                }
                if ((objId != 0) && (*pSlot != -1) && (activeCount < 4))
                {
                    (&DAT_01194ae0)[activeCount] = objId; // Add to active objective list (max 4)
                    activeCount = activeCount + 1;
                }
                pSlot = pSlot + 1;                     // Move to next slot
                objCount = objCount - 1;
                DAT_01162387 = activeCount;            // Update global count each iteration
            } while (objCount != 0);
        }
    }
    return;
}