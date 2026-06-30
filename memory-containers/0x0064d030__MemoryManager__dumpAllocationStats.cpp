// FUNC_NAME: MemoryManager::dumpAllocationStats
void MemoryManager::dumpAllocationStats(void)
{
    // Iterate through linked list of allocation statistics nodes
    AllocationStatsNode* node = g_allocationStatsList; // DAT_012059ec
    while (node != nullptr)
    {
        // Print initial allocation statistics
        if (node->initialCount != 0)
        {
            float avgSize = (float)node->initialTotalSize / (float)node->initialCount;
            DebugPrint("%s (Initial) - Count: %d   Avg Size: %g",
                       node->name, node->initialCount, avgSize);
        }
        // Print partial allocation statistics
        if (node->partialCount != 0)
        {
            float avgSize = (float)node->partialTotalSize / (float)node->partialCount;
            DebugPrint("%s (Partial) - Count: %d   Avg Size: %g",
                       node->name, node->partialCount, avgSize);
        }
        node = node->next; // +0x70
    }
}